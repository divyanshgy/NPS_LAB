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
	int buff[30],str[30];
	struct sockaddr_in serv_addr,c_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	printf("Enter the 4 bit data one by one: \n");
	scanf("%d",&buff[2]);
	scanf("%d",&buff[4]);
	scanf("%d",&buff[5]);
	scanf("%d",&buff[6]);
	printf("Entered 4 bit data: %d%d%d%d\n",buff[2],buff[4],buff[5],buff[6]);
	buff[0]=buff[2]^buff[4]^buff[6];
	buff[1]=buff[0]^buff[1]^buff[4];
	buff[3]=buff[4]^buff[5]^buff[6];
	send(sockfd,str,sizeof(str),0);
	close(sockfd);
}