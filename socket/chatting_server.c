/*
pineoc, 2015-05-04
week 10 network programming
multiThread chatting
server code
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
 
#define BUF_SIZE 1024
void error_handling(char* msg);

void* handle_clnt(void* arg);
void send_msg(char* msg,int len);

int clnt_socks[10];
int clnt_cnt;
pthread_mutex_t mutex;
 
int main(int argc,char* argv[])
{
	int serv_sock,clnt_sock;
	char msg[BUF_SIZE];
	int str_len,i;
	pthread_t t_id;
 
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_sz;

	pthread_mutex_init(&mutex,NULL);
 
	if(argc!=2)
	{
		printf("Usage :%s <port>\n",argv[0]);
		exit(1);
	}
	serv_sock = socket(PF_INET,SOCK_STREAM,0);
	if(serv_sock==-1)
        error_handling("socket() err");
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind() err");
 
	if(listen(serv_sock,5)==-1)
		error_handling("listen() err");
 
	clnt_addr_sz = sizeof(clnt_addr);
 
	while(1)
	{
		clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_sz);
		if(clnt_sock==-1)
      		error_handling("accept() err");
		pthread_mutex_lock(&mutex);
		clnt_socks[clnt_cnt++]=clnt_sock;
		pthread_mutex_unlock(&mutex);

		pthread_create(&t_id,NULL,handle_clnt,(void*)&clnt_sock);
		pthread_detach(t_id);
		printf("Connected IP : %s \n",inet_ntoa(clnt_addr.sin_addr));
	}
	close(serv_sock);
 
	return 0;
}
 
void error_handling(char* msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}

void send_msg(char* msg,int len)
{
	int i;
	pthread_mutex_lock(&mutex);
	for(i=0;i<clnt_cnt;i++)
	{
		write(clnt_socks[clnt_cnt],msg,len);
	}
	pthread_mutex_unlock(&mutex);
}

void* handle_clnt(void* arg)
{
	int i=0;
	int clnt_sock=*((int*)arg);
	int str_len=0;
	char msg[BUF_SIZE];
	
	while((str_len=read(clnt_sock,msg,sizeof(msg)))!=0)
		send_msg(msg,str_len);

	pthread_mutex_lock(&mutex);
	for(i=0;i<clnt_cnt;i++)
	{
		if(clnt_sock==clnt_socks[i])
		{
			while(i++<clnt_cnt-1)
				clnt_socks[i]=clnt_socks[i+1];
			break;
		}
	}
	clnt_cnt--;

	pthread_mutex_unlock(&mutex);
	close(clnt_sock);

	return NULL;
}
