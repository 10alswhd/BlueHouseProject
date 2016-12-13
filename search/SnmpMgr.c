/*****************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 *  Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * Simple SNMP-client for Windows only.
 * Example usage:
 *   Returns system name:
 *   snmpmgr snmp://<host>/1.3.6.1.2.1.1.1.0
 *
 *   Returns packet-count at iface 3:
 *   snmpmgr snmp://<host>/1.3.6.1.2.1.2.2.1.10.3
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <curl/curl.h>
#include <windows.h>
#include <snmp.h>
#include <mgmtapi.h>

/* Use MSVC CrtDebug in debug-mode ('-MD' or '-MT').
 * This MUST match what was used to build libcurl.dll.
 */
#if defined(_DEBUG)
  #define _CRTDBG_MAP_ALLOC
  #undef _malloca          /* Avoid MSVC-9 <malloc.h>/<crtdbg.h> name-clash */
  #include <crtdbg.h>
#else
 /* Program bombs with this in....
  */
//#include <memdebug.h>
#endif

#define DIM(x)        (sizeof(x) / sizeof(x[0]))
#define SNMP_ILL_OID  -1
#define SNMP_GEN_ERR  -2

#ifndef SNMP_PORT
#define SNMP_PORT 161
#endif

#if (_WIN32_WINNT < 0x0600)
  /*
   * Borrowed from ../../lib/inet_ntop.c
   */
  extern char *Curl_inet_ntop (int af, const void *addr, char *buf, size_t size);
  #define inet_ntop(af, addr, buf, size) Curl_inet_ntop(af, addr, buf, size)
#endif

struct search_list {
       DWORD       value;
       const char *name;
     };

/*
 * List of all WinSNMP errors libcurl is able to produce.
 */
static const struct search_list snmp_errs[] = {
     /* from <MgmtAPI.h> */
     { SNMP_MGMTAPI_TIMEOUT,                "Timeout" },
     { SNMP_MGMTAPI_SELECT_FDERRORS,        "Select Fd errors" },
     { SNMP_MGMTAPI_TRAP_ERRORS,            "Trap _Errors" },
     { SNMP_MGMTAPI_TRAP_DUPINIT,           "Trap Dupinit" },
     { SNMP_MGMTAPI_NOTRAPS,                "No traps" },
     { SNMP_MGMTAPI_AGAIN,                  "Again" },
     { SNMP_MGMTAPI_INVALID_CTL,            "Invalid Control" },
     { SNMP_MGMTAPI_INVALID_SESSION,        "Invalid Session" },
     { SNMP_MGMTAPI_INVALID_BUFFER,         "Invalid Buffer" },

     /* from <Snmp.h> */
     { SNMP_ERRORSTATUS_NOERROR,            "No Error" },
     { SNMP_ERRORSTATUS_TOOBIG,             "Too Big" },
     { SNMP_ERRORSTATUS_NOSUCHNAME,         "No Such Name" },
     { SNMP_ERRORSTATUS_BADVALUE,           "Bad Value" },
     { SNMP_ERRORSTATUS_READONLY,           "Read Only" },
     { SNMP_ERRORSTATUS_GENERR,             "Gen Error" },
     { SNMP_ERRORSTATUS_NOACCESS,           "No Access" },
     { SNMP_ERRORSTATUS_WRONGTYPE,          "Wrong Type" },
     { SNMP_ERRORSTATUS_WRONGLENGTH,        "Wrong Length" },
     { SNMP_ERRORSTATUS_WRONGENCODING,      "Wrong Encoding" },
     { SNMP_ERRORSTATUS_WRONGVALUE,         "Wrong Value" },
     { SNMP_ERRORSTATUS_NOCREATION,         "No Creation" },
     { SNMP_ERRORSTATUS_INCONSISTENTVALUE,  "Inconsistent Value" },
     { SNMP_ERRORSTATUS_RESOURCEUNAVAILABLE,"Resource Unavailable" },
     { SNMP_ERRORSTATUS_COMMITFAILED,       "Commit Failed" },
     { SNMP_ERRORSTATUS_UNDOFAILED,         "Undo Failed" },
     { SNMP_ERRORSTATUS_AUTHORIZATIONERROR, "Authorization Error" },
     { SNMP_ERRORSTATUS_NOTWRITABLE,        "Not Writable" },
     { SNMP_ERRORSTATUS_INCONSISTENTNAME,   "Inconsistent name" }
   };

static SOCKET snmpmgr_getsock (void *clientp,
                               curlsocktype purpose,
                               struct curl_sockaddr *addr)
{
  (void) clientp;
  (void) purpose;
  (void) addr;
  return socket (AF_INET, SOCK_DGRAM, 0);
}


static CURLcode build_varbind_list (const char *string, SnmpVarBindList **listp)
{
  AsnObjectIdentifier oid;
  SnmpVarBind     *vb = NULL;
  SnmpVarBindList *vb_list = NULL;
  CURLcode rc;
  char    *oid_str = malloc (strlen(string)+2);

  if (!oid_str) {
    rc = CURLE_OUT_OF_MEMORY;
    goto fail;
  }

  vb = calloc (sizeof(*vb), 1);
  if (!vb) {
    rc = CURLE_OUT_OF_MEMORY;
    goto fail;
  }

  vb_list = calloc (sizeof(*vb_list), 1);
  if (!vb_list) {
    rc = CURLE_OUT_OF_MEMORY;
    goto fail;
  }

  *oid_str = '.';
  strcpy (oid_str+1, string);
  if (!SnmpMgrStrToOid(oid_str, &oid)) {
    printf ("Illegal OID %s\n", oid_str);
    rc = SNMP_ILL_OID;
    goto fail;
  }
  free (oid_str);
  memcpy (&vb->name, &oid, sizeof(vb->name));
  vb->value.asnType = ASN_NULL;
  vb_list->len = 1;
  vb_list->list = vb;
  *listp = vb_list;
  return (CURLE_OK);

fail:
  if (oid_str)
    free (oid_str);
  if (vb_list)
    free (vb_list);
  if (vb)
    free (vb);
  return (rc);
}

static BOOL free_varbind_list (SnmpVarBindList **listp)
{
  SnmpVarBindList *vb_list;

  if (!listp || !*listp)
    return (FALSE);

  vb_list = *listp;
  SnmpUtilOidFree (&vb_list->list->name);
  vb_list->len = 0;
  free (vb_list->list);
  free (vb_list);
  *listp = NULL;
  return (TRUE);
}

static void dump_response (const AsnObjectSyntax *asn)
{
  char        buf[1024], *p = buf;
  const char *end = buf + sizeof(buf) - 1;
  unsigned    i, len;
  BOOL        ishex;

  switch (asn->asnType) {
    case ASN_OCTETSTRING:
         p += sprintf (p, "String: ");
         if (!asn->asnValue.string.stream) {
           p += sprintf (p, "NULL");
           break;
         }
         ishex = !isprint (asn->asnValue.string.stream[0]);
         for (i = 0; i < asn->asnValue.string.length; i++)
           p += sprintf (p, ishex ? "%02X" : "%c", asn->asnValue.string.stream[i]);
         break;

    case ASN_UNSIGNED32:
         p += sprintf (p, "Unsigned32: "
                          "%lu", asn->asnValue.unsigned32);
         break;

    case ASN_INTEGER32:
         p += sprintf (p, "Integer32: "
                          "%lu", asn->asnValue.number);
         break;

    case ASN_TIMETICKS:
         p += sprintf (p, "Ticks: "
                          "%lu", asn->asnValue.ticks);
         break;

    case ASN_GAUGE32:
         p += sprintf (p, "Gauge32: "
                          "%lu", asn->asnValue.gauge);
         break;

    case ASN_COUNTER32:
         p += sprintf (p, "Counter32: "
                          "%lu", asn->asnValue.counter);
         break;

    case ASN_COUNTER64:
         p += sprintf (p, "Counter64: "
                          "%I64u", *(unsigned __int64*)&asn->asnValue.counter64);
         break;

    case ASN_IPADDRESS:
         len = asn->asnValue.address.length;
         if (len == 4) {
           p += sprintf (p, "IPv4 addr: ");
           inet_ntop (AF_INET, asn->asnValue.address.stream, p, end-p);
         }
         else if (len == 16) {
           p += sprintf (p, "IPv6 addr: ");
           inet_ntop (AF_INET6, asn->asnValue.address.stream, p, end-p);
         }
         else
           p += sprintf (p, "IPv?? addr ");
         break;

    case ASN_OBJECTIDENTIFIER:
         for (i = 0; i < asn->asnValue.object.idLength; i++)
           p += sprintf (p, ".%u", asn->asnValue.object.ids[i]);
         break;

    case ASN_OPAQUE:
         p += sprintf (p, "Opaque: ");
         for (i = 0; i < asn->asnValue.arbitrary.length; i++)
           p += sprintf (p, "%02X ", asn->asnValue.arbitrary.stream[i]);
         break;

    case ASN_NULL:
         p += sprintf (p, "ASN NULL");
         break;
  }
  if (p == buf)
       puts ("No data");
  else puts (buf);
}

/*
 * Search 'list' for 'type' and return it's name.
 */
static const char *list_lookup (DWORD value, const struct search_list *list,
                                int num)
{
  while (num > 0 && list->name) {
    if (list->value == value)
      return (list->name);
    num--;
    list++;
  }
  return (NULL);
}

const char *win_strerror (DWORD err)
{
  static char buf[200];

  if (!FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err,
                      LANG_NEUTRAL, buf, sizeof(buf), NULL))
    _snprintf (buf, sizeof(buf), "Unknown error %lu (%#lx)", err, err);
  return (buf);
}

/*
 * Cannot use win_strerror() directly since WinSNMP errors overlaps
 * with system errors.
 */
const char *snmp_strerror (int err)
{
  const char *p = list_lookup (err, snmp_errs, DIM(snmp_errs));

  if (p)
     return (p);
  return win_strerror (err);
}

/*
 * The main SNMP function; build the var-list, connect, send the request
 * and dump the response.
 */
CURLcode snmp_main (const char *host, const char *oid)
{
  LPSNMP_MGR_SESSION session;
  SnmpVarBindList   *list = NULL;
  AsnInteger         errStatus = 0, errIndex = 0;
  int                timeout = 500;
  int                i, retries = 1;
  CURLcode           rc;

  rc = build_varbind_list (oid, &list);
  if (rc != CURLE_OK)
     return (rc);

  session = SnmpMgrOpen ((LPSTR)host, "public", timeout, retries);
  if (!session) {
    printf ("SNMP Mgr: %s\n", snmp_strerror(GetLastError()));
    rc = SNMP_GEN_ERR;
    goto quit;
  }

  if (!SnmpMgrRequest(session, SNMP_PDU_GET, list, &errStatus, &errIndex) ||
      errStatus > 0) {
    if (errStatus == SNMP_ERRORSTATUS_NOSUCHNAME)
      printf ("SNMP Mgr: no such OID %s\n", oid);
    else
      printf ("SNMP Mgr: err-status %lu, err-index %lu, %s\n",
              errStatus, errIndex, snmp_strerror(GetLastError()));
    rc = SNMP_GEN_ERR;
    goto quit;
  }

  for (i = 0; i < (int)list->len; i++)
    dump_response (&list->list[i].value);
  rc = CURLE_OK;

quit:
  if (session)
    SnmpMgrClose (session);
  if (list != NULL)
    free_varbind_list (&list);
  return (rc);
}

int main (int argc, char **argv)
{
  CURL *data;
  char  host[200+1], oid[200+1];
  int   verbose = 0;
  int   winsnmp_only = 0;

  if (argc > 1 && !strcmp(argv[1],"-v")) {
    verbose = 1;
    argc--;
    argv++;
  }

  if (argc > 1 && !strcmp(argv[1],"-w")) {
    winsnmp_only = 1;
    argc--;
    argv++;
  }

  if (argc < 2 ||
      sscanf(argv[1],"snmp://%200[^/]/%200s",host,oid) != 2) {
    printf ("Usage: snmpmgr [-v] [-w] <snmp://host/OID>\n");
    return (-1);
  }

  if (!winsnmp_only) {
    data = curl_easy_init();

    curl_easy_setopt (data, CURLOPT_CONNECT_ONLY, 1);
    curl_easy_setopt (data, CURLOPT_URL, host);
    curl_easy_setopt (data, CURLOPT_PORT, SNMP_PORT);
    curl_easy_setopt (data, CURLOPT_OPENSOCKETFUNCTION, snmpmgr_getsock);
    if (verbose)
       curl_easy_setopt (data, CURLOPT_VERBOSE, 1);
    curl_easy_perform (data);
  }

  snmp_main (host, oid);

  if (!winsnmp_only)
     curl_easy_cleanup (data);

  return (0);
}
