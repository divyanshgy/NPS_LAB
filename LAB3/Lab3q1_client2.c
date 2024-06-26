#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define myport 1388
int main(){
	int sockfd;
	struct sockaddr_in serv_addr;
	char buff[50];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	strcpy(buff," Technology");
	send(sockfd,buff,sizeof(buff),0);
	char* ipbuffer;
	char ip[50];
	ipbuffer=inet_ntoa(serv_addr.sin_addr);
	strcpy(ip,ipbuffer);
	ip[strlen(ip)]='\0';
	printf("\n IP is: %s",ip);
	send(sockfd,ip,sizeof(ip),0);
	close(sockfd);
}
