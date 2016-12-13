#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ifdef __sun
#define _XPG4_2 1
#endif

#ifndef _WIN32

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/types.h>
#include <arpa/inet.h>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include <glib.h>

#include "stunagent.h"
#include "agent-priv.h"
#include "agent.h"

#ifndef SOL_IP
# define SOL_IP IPPROTO_IP
#endif

#ifndef SOL_IPV6
# define SOL_IPV6 IPPROTO_IPV6
#endif

#ifndef IPV6_RECVPKTINFO
# define IPV6_RECVPKTINFO IPV6_PKTINFO
#endif

#ifndef MAX_CANDS
# define MAX_CANDS 3
#endif

/** Default port for STUN binding discovery */
#define IPPORT_STUN 3456

static const uint16_t known_attributes[] =  {
  0
};

static GMainLoop *loop = NULL;
static NiceCandidate *remote_candidate[MAX_CANDS];
static GMutex setting_remote_candidates_mutex;
static GMutex adding_remote_cand;
static GCond candidate_gathering_done;
static gboolean all_remote_addr_added = FALSE;
static NiceAddress addr_remote[MAX_CANDS];
static GSList* remote_list = NULL;

/*
 * Creates a listening socket
 */
static int listen_socket (unsigned int port)
{
  int yes = 1;
  int fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  
  if (fd == -1)
  {
    perror ("Error opening IP port");
    return -1;
  }
  if (fd < 3)
    goto error;

  struct sockaddr_in addr;
  memset (&addr, 0, sizeof (addr));
  addr.sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
  addr.sin_port = htons(port);
  setsockopt (fd, SOL_IP, IP_RECVERR, &yes, sizeof (yes));
  
  if (bind (fd, (struct sockaddr_in *)&addr, sizeof (struct sockaddr_in)))
  {
    perror ("Error opening IP port");
    goto error;
  }

  return fd;

error:
  close (fd);
  return -1;
}

static int dgram_process (int sock, StunAgent *oldagent, StunAgent *newagent)
{
  struct sockaddr_storage addr;
  socklen_t addr_len;
  uint8_t buf[STUN_MAX_MESSAGE_SIZE];
  size_t buf_len = 0;
  size_t len = 0;
  StunMessage request;
  StunMessage response;
  StunValidationStatus validation;
  StunAgent *agent = NULL;

  addr_len = sizeof (struct sockaddr_in);
  g_debug("listening for STUN requests");
  len = recvfrom (sock, buf, sizeof(buf), 0,
      (struct sockaddr *)&addr, &addr_len);
  if (buf_len == (size_t)-1)
    return -1;

  validation = stun_agent_validate (newagent, &request, buf, len, NULL, 0);

  if (validation == STUN_VALIDATION_SUCCESS) {
    agent = newagent;
  }
  else {
    validation = stun_agent_validate (oldagent, &request, buf, len, NULL, 0);
    agent = oldagent;
  }

  /* Unknown attributes */
  if (validation == STUN_VALIDATION_UNKNOWN_REQUEST_ATTRIBUTE)
  {
    buf_len = stun_agent_build_unknown_attributes_error (agent, &response, buf,
        sizeof (buf), &request);
    goto send_buf;
  }

  /* Mal-formatted packets */
  if (validation != STUN_VALIDATION_SUCCESS ||
      stun_message_get_class (&request) != STUN_REQUEST) {
    return -1;
  }

  switch (stun_message_get_method (&request))
  {
    case STUN_BINDING:
      stun_agent_init_response (agent, &response, buf, sizeof (buf), &request);
      if (stun_message_has_cookie (&request))
        stun_message_append_xor_addr (&response,
            STUN_ATTRIBUTE_XOR_MAPPED_ADDRESS,
            (struct sockaddr *)&addr, addr_len);
      else
         stun_message_append_addr (&response, STUN_ATTRIBUTE_MAPPED_ADDRESS,
             (struct sockaddr *)&addr, addr_len);
      break;

    default:
      if (!stun_agent_init_error (agent, &response, buf, sizeof (buf),
              &request, STUN_ERROR_BAD_REQUEST))
        return -1;
  }

  buf_len = stun_agent_finish_message (agent, &response, NULL, 0);

send_buf:
  while(!all_remote_addr_added) {
    g_mutex_lock(&setting_remote_candidates_mutex);
    g_cond_wait(&candidate_gathering_done, &setting_remote_candidates_mutex);
    len = sendto (sock, buf, buf_len, 0,
        (struct sockaddr *)&addr, addr_len);
    g_debug("STUN response sent");
    g_main_loop_quit(loop);
    return (len < buf_len) ? -1 : 0;
  }
  return -1;
}


static gpointer stun_thread_func (const gpointer user_data)
{
  StunAgent oldagent;
  StunAgent newagent;
  int sock = listen_socket (IPPORT_STUN);
  
  if (sock == -1)
    return GINT_TO_POINTER(-1);

  stun_agent_init (&oldagent, known_attributes,
      STUN_COMPATIBILITY_RFC3489, 0);
  stun_agent_init (&newagent, known_attributes,
      STUN_COMPATIBILITY_RFC5389, STUN_AGENT_USAGE_USE_FINGERPRINT);

  for (;;)
    dgram_process (sock, &oldagent, &newagent);

  return NULL;
}

static NiceCandidate* nice_candidate_from_nice_address(NiceAgent* agent, guint stream_id, NiceAddress* addr)
{
  NiceCandidate *cand = nice_candidate_new(NICE_CANDIDATE_TYPE_HOST);
  cand->addr = *addr;
  cand->stream_id = stream_id;
  
  gchar *ufrag = NULL, *password = NULL;
  nice_agent_get_local_credentials(agent, stream_id, &ufrag, &password);
  
  cand->username = ufrag;
  cand->password = password;

  g_free(ufrag);
  g_free(password);

  return cand;
}

static void cb_set_new_remote_address(NiceAgent *agent, guint stream_id,guint component_id, guint state, gpointer user_data)
{
  g_debug("test-new-dribble-mode: %s", G_STRFUNC);
  static int index = 1;
  if( state >= NICE_COMPONENT_STATE_GATHERING && state <= NICE_COMPONENT_STATE_FAILED && index < MAX_CANDS) {
    g_debug("Index is : %d", index);
    remote_list = g_slist_append(remote_list, remote_candidate[index]);
    index++;
    g_assert(nice_agent_set_remote_candidates(agent, stream_id, NICE_COMPONENT_TYPE_RTP, remote_list));
  }

  if(index >= MAX_CANDS && !all_remote_addr_added) {
    g_debug("Signalling STUN thread");
    g_mutex_lock(&setting_remote_candidates_mutex);
    all_remote_addr_added = TRUE;
    g_cond_signal(&candidate_gathering_done);
    g_mutex_unlock(&setting_remote_candidates_mutex);
  }
}

gint
main (void)
{
#if !GLIB_CHECK_VERSION(2,31,0)
  g_thread_init(NULL);
#endif

  g_type_init ();

  NiceAgent *agent;
  NiceAddress addr_local;
  guint stream_id;
  GThread *stun_thread;

  int i = 0;
 
  g_debug("dribble mode test initiated");
  
#if !GLIB_CHECK_VERSION(2,31,8)
  g_thread_init(NULL);
#endif

  nice_address_init (&addr_local);

  for(i = 0; i < MAX_CANDS; i++) {
    nice_address_init (&addr_remote[i]);
  }

  loop = g_main_loop_new(NULL, FALSE);

  g_mutex_init(&setting_remote_candidates_mutex);
  g_mutex_init(&adding_remote_cand);
  g_cond_init(&candidate_gathering_done);
  agent = nice_agent_new (g_main_loop_get_context (loop), NICE_COMPATIBILITY_RFC5245);

  // Start STUN Daemon in another thread
  stun_thread = g_thread_new("listen for STUN requests", stun_thread_func, NULL);

  g_assert (nice_address_set_from_string (&addr_local, "127.0.0.1"));
  g_assert (agent->local_addresses == NULL);

  /* add one local address */
  nice_agent_add_local_address (agent, &addr_local);
  g_assert (agent->local_addresses != NULL);
  g_assert (g_slist_length (agent->local_addresses) == 1);
  g_assert (nice_address_equal (agent->local_addresses->data, &addr_local));

  /* add a stream */
  stream_id = nice_agent_add_stream (agent, 1);
 
  // Set stun server and port
  g_object_set (G_OBJECT (agent), "stun-server", "127.0.0.1",  NULL);
  g_object_set (G_OBJECT (agent), "stun-server-port", IPPORT_STUN,  NULL);

  g_assert (nice_address_set_from_string (&addr_remote[0], "127.0.0.1"));
  g_assert (nice_address_set_from_string (&addr_remote[1], "172.1.0.1"));
  g_assert (nice_address_set_from_string (&addr_remote[2], "129.0.0.1"));


  for( i = 0; i < MAX_CANDS; i++) {  
    nice_address_set_port (&addr_remote[i], 2345);
    g_assert (nice_address_is_valid(&addr_remote[i]));
    remote_candidate[i] = nice_candidate_from_nice_address(agent, stream_id, &addr_remote[i]);
  }
 
  nice_agent_gather_candidates (agent, stream_id);

  remote_list = g_slist_append(remote_list, remote_candidate[0]); 
  nice_agent_set_remote_candidates(agent, stream_id, NICE_COMPONENT_TYPE_RTP, remote_list);

  g_signal_connect (G_OBJECT (agent), "component-state-changed",
      G_CALLBACK (cb_set_new_remote_address), NULL);


  g_main_loop_run(loop);

  // Clean up
  g_slist_free(remote_list);
  g_thread_unref(stun_thread);
  g_object_unref(agent);
  g_main_loop_unref(loop);
  return 0;
}

#else
int main (int argc, char **argv) {
  return 0;
}

#endif
