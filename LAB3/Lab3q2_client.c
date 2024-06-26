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
	char ip[50];
	strcpy(ip,"127.0.0.1");
	send(sockfd,ip,sizeof(ip),0);
	printf("Type 1st string: \n");
	scanf("%s",buff);
	send(sockfd,buff,sizeof(buff),0);
	printf("\nType string 2: ");
	scanf("%s", buff);
	send(sockfd,buff,sizeof(buff),0);
	recv(sockfd,buff,sizeof(buff),0);
	printf("\n%s\n", buff);
	close(sockfd);
}