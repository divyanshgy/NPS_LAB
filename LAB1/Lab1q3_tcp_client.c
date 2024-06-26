#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#define myport 1465
int main(){
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in c_addr;
	c_addr.sin_family=AF_INET;
	c_addr.sin_port=htons(myport);
	c_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(c_addr.sin_zero,'\0',sizeof(c_addr.sin_zero));

	connect(sockfd,(struct sockaddr*)&c_addr,sizeof(c_addr));

	printf("Connected to the server...");
	close(sockfd);
}