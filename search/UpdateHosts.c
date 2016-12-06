/**
 * update hosts for linux
 * @author    TX <txthinking@gmail.com>
 * @link    http://blog.txthinking.com
 * @license    http://www.gnu.org/licenses/old-licenses/gpl-2.0.html     GNU GPL v2
 * @version 1.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define HOSTS_PATH "/etc/hosts"
#define SEARCH_STRING "#TX-HOSTS"

int main(){
	FILE *lfp, *rfp;
	char line[1000];
	char yourself[100000];
	char backup[1000];
	char ip[INET_ADDRSTRLEN];
	struct sockaddr_in socketAddress;
	int socketFd;
	int isHeadEnd = 0;

	int getIpByDomain(const char *domain, char ip[]);

	/*read yourself hosts*/
	memset(&yourself, 0, sizeof(yourself));
	lfp = fopen(HOSTS_PATH, "r");
	while(!feof(lfp)){
		memset(&line, 0, sizeof(line));
		fgets(line, 1000, lfp);
		if(strstr(line, SEARCH_STRING)){
			break;
		}
		strcat(yourself, line);
	}
	fclose(lfp);
	strcat(yourself, "\n");
	strcat(yourself, SEARCH_STRING);
	strcat(yourself, "\n");

	/*backup hosts file*/
	memset(&backup, 0, sizeof(backup));
	strcat(backup, HOSTS_PATH);
	strcat(backup, "-BAK-TX-HOSTS");
	rename(HOSTS_PATH, backup);

	/*create and write yourself hosts and remote hosts to hosts file*/
	lfp = fopen(HOSTS_PATH, "w");
	fputs(yourself, lfp);
	getIpByDomain("services.txthinking.com", ip);
	memset(&socketAddress, 0, sizeof(socketAddress));
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.s_addr = inet_addr(ip);
	socketAddress.sin_port = htons(80);
	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	connect(socketFd, (struct sockaddr * )&socketAddress, sizeof(socketAddress));
	rfp = fdopen(socketFd, "w+");
	char in[] = "GET http://services.txthinking.com/tx-hosts/hosts HTTP/1.1\r\nHost: services.txthinking.com\r\nConnection: close\r\n\r\n";
	fputs(in, rfp);
	while(!feof(rfp)){
		memset(&line, 0, sizeof(line));
		fgets(line, 1000, rfp);
		if(isHeadEnd){
			fputs(line, lfp);
		}
		if(strcmp(line, "\r\n") == 0){
			isHeadEnd = 1;
		}
	}
	fclose(rfp);
	fclose(lfp);
    close(socketFd);
    
    printf("Success\n");
    
	return 0;
}

/**
 * get ip from a domain
 */
int getIpByDomain(const char *domain, char ip[]){
	struct addrinfo *addrInfo;
	struct sockaddr_in *sockAddr;
	const char strptr[INET_ADDRSTRLEN];

	getaddrinfo(domain, NULL, NULL, &addrInfo);
	sockAddr = (struct sockaddr_in *)addrInfo->ai_addr;
    inet_ntop(AF_INET, &sockAddr->sin_addr, strptr, INET_ADDRSTRLEN);
    strcpy(ip, strptr);
   
    return 0;
}
