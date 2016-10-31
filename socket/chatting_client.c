/*
pineoc, 2015-05-04
week 10 network programming
multiThread chatting
client code
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
 
#define BUF_SIZE 1024
#define NAME_SIZE 20

void error_handling(char* msg);

void* send_msg(void* arg);
void* rcv_msg(void* arg);

char msg[BUF_SIZE];
char name[NAME_SIZE]="[DEFAULT]";
pthread_mutex_t mutex;
 
int main(int argc,char* argv[])
{
	int sock;
	char msg[BUF_SIZE];
	int str_len,i;
	pthread_t snd_thread,rcv_thread;
	void* thread_return;

 
	struct sockaddr_in serv_addr;
	socklen_t clnt_addr_sz;

	pthread_mutex_init(&mutex,NULL);
 
	sock = socket(PF_INET,SOCK_STREAM,0);
	if(sock==-1)
        error_handling("socket() err");
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
 
	if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("connect() error");

	pthread_create(&snd_thread,NULL,send_msg,(void*)&sock);
	pthread_create(&rcv_thread,NULL,rcv_msg,(void*)&sock);
	pthread_join(snd_thread,&thread_return);
	pthread_join(rcv_thread,&thread_return);
	close(sock);

	return 0;
}
 
void error_handling(char* msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}
void* send_msg(void* arg)
{
	int sock = *((int*)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	while(1)
	{
		pthread_mutex_lock(&mutex);
		fgets(msg,BUF_SIZE,stdin);
		if(!strcmp(msg,"q\n")||!strcmp(msg,"Q\n"))
		{
			shutdown(sock,SHUT_WR);
			return;
		}
		write(sock,msg,strlen(msg));
		pthread_mutex_unlock(&mutex);
	}
}

void* rcv_msg(void* arg)
{
	int sock = *((int*)arg);
	while(1)
	{
		pthread_mutex_lock(&mutex);
		int str_len = read(sock,msg,BUF_SIZE);
		if(str_len==0)
			return;
		msg[str_len]=0;
		printf("Message from server : %s",msg);
		pthread_mutex_unlock(&mutex);
	}
}
