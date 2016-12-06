#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include "libmill.h"

//#include "list.h"
#include "slist.h"

//coroutine void client(int port) {
//}

//bool search(node* list, int n){
//  node* ptr = list;
//  while(ptr != NULL){
//    if(ptr->n == n){
//      return true;
//    }
//    ptr = ptr->next;
//  }
//  return false;
//}



///*  Takes a pointer to a member variable and computes pointer to the structure
//    that contains it. 'type' is type of the structure, not the member. */
//#define mill_cont(ptr, type, member) \
//    (ptr ? ((type*) (((char*) ptr) - offsetof(type, member))) : NULL)
//static struct mill_slist mill_all_fds = {0};
//struct mill_fd_item {
//    char *path;
//    int fd;
////    struct mill_list_item *item;
//    struct mill_slist_item *next;
////    struct mill_list_item *prev;
//};
// max open files we expect
//#define FDS 100
//static struct file {
//  char *path;
//  int fd;
//} files[FDS];

typedef struct node {
  int fd;
  char *path;
  struct node *next;
} node;

typedef struct list {
  node *first;
  node *last;
} list;

void list_init(list *self) {
  node *head = malloc(sizeof(node));
  head->next = NULL;
  self->first = head;
  self->last = head;
}

void push(list *self, node *new){
  new->next = NULL;
  self->last->next = new;
  self->last = new;
}

int search(list *self, char *path){
  node *look = self->first;
  while(look){
    if(look->path == path)
      return look->fd;
    look = look->next;
  }
  return 0;
}



//void node_push(struct node *head, struct node *new) {
//    new->next = NULL;
//    self->last = NULL;
//}

int main(int argc, char *argv[]) {
  int fd, f, d, n, p;
  size_t rc;
  ssize_t sz;
  ipaddr addr;
  ipaddr tcpaddr = iplocal(NULL, 45000, 0);
  tcpsock ls = tcplisten(tcpaddr, 10);

  udpsock s = udplisten(iplocal(NULL, 46000, 0));
  printf("udp listening on 46000, awaiting inbound\n");

  static list head = {0};
  list_init(&head);

//  files[0].path = "init";
//  files[0].fd = 0;
  //struct mill_fd_item *fds;
  //fds->path = "init";
  //fds->fd = 0;
//  node first;
//  first.fd = 1;
//  first.path = "hey";
//  first.next = NULL;
//  node *new;
//  if(new == NULL)
//    exit(1);
//  new->fd = 0;
//  new->path = "sup";
//  new->next = &first;

  while(1) {
    char path[256];
    char buf[4096];
    rc = udprecv(s, &addr, path, sizeof(path), -1);
    if(errno != 0)
      break;
    printf("recved a buffer: %s of size %ld\n", path, rc);
    int fd = search(&head, path);
    if (fd){
      printf("search print, got one: %d\n", fd);
    } else {
      printf("nada: %d\n", fd);
      node *new = malloc(sizeof(node));
      new->path = path;
      new->fd = open(path, O_RDONLY);
      push(&head, new);
    }






//    f = 1;
//    d = FDS;
//    while(d--){
//      if (files[d].path){
//        if(files[d].path == path){
//          f = 0;
//          p = d;
//          printf("path match: %s\n",files[d].path);
//          break;
//        }
//      } else {
//        n = d;
//      }
//    }


//    if (f) {
//      fd = open(path, O_RDONLY);
//      if(fd == -1)
//        printf("error opening file\n");
//      sz = read(fd, &buf, sizeof(buf));
//      printf("read %lu bytes from file:\n%s\n", sz, buf);
//      files[n].fd = fd;
//      files[n].path = path;
//    } else {
//      printf("what is p: %d\n",p);
//    }


    fd = open(path, O_RDONLY);
    if(fd == -1)
      printf("error opening file\n");
    sz = read(fd, &buf, sizeof(buf));
    //printf("read %lu bytes from file\n", sz);
    printf("read %lu bytes from file:\n%s\n", sz, buf);
//    tcpsock cs = tcpconnect(tcpaddr, -1);
//    tcpsock as = tcpaccept(ls, -1);
//    printf("tcp connection established.\n");
//    tcpclose(cs);
//    tcpclose(as);
//    close(fd);
  }

  return 0;
}
