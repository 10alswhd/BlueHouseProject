include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#ifndef __syscall_slong_t
#define __syscall_slong_t long
#endif

// cc -m64 -o testbug64 testbug.c
// cc -m32 -o testbug32 testbug.c

int main(int argc, char * args[], char * envp[])
{
// get a system V IPC message queue
int msgid = msgget(75, 0777 | IPC_CREAT);
printf("msg id is %d\n", msgid);
if (msgid < 0)
{
printf("errno %d : %s\n", errno, strerror(errno));
return 1;
}

// declare a message
struct {
__syscall_slong_t mtype;
char mtext[512];
} __attribute__((aligned(32))) msg;

// populate the message
msg.mtype = 2;
strcpy(msg.mtext, "test message");

// send the message
int rv = msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
printf("Sent status %d\n", rv);
if (rv < 0)
{
printf("errno %d : %s\n", errno, strerror(errno));
if (msgid > -1) msgctl(msgid, IPC_RMID, 0);
return 2;
}

struct {
__syscall_slong_t mtype;
char mtext[1024];
} __attribute__((aligned(32))) msgr;

msgr.mtext[0] = '\0';

// receive any message of id 2 or less
ssize_t len = msgrcv(msgid, &msgr, sizeof(msgr.mtext), -2, IPC_NOWAIT);

printf("Received %d bytes (of %d possible), message type %ld : %s\n", (int)len, sizeof(msgr.mtext), msgr.mtype, msgr.mtext);
if (len < 0)
{
printf("errno %d : %s\n", errno, strerror(errno));
}

msgr.mtext[0] = '\0';

// receive any message of id 2
len = msgrcv(msgid, &msgr, sizeof(msgr.mtext), 2, IPC_NOWAIT);

printf("Received %d bytes (of %d possible), message type %ld : %s\n", (int)len, sizeof(msgr.mtext), msgr.mtype, msgr.mtext);
if (len < 0)
{
printf("errno %d : %s\n", errno, strerror(errno));
}

if (msgid > -1) msgctl(msgid, IPC_RMID, 0);
return 0;
}
