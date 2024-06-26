#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define myport 1388
int main(){
	int sockfd,size;
	char buff[30];
	struct sockaddr_in serv_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	
	printf("Enter alphanumeric string: ");
  	scanf("%s",buff);
  	send(sockfd, buff, sizeof(buff), 0);
	close(sockfd);
}