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
	char a[30],b[30],buff[30];
	struct sockaddr_in serv_addr,c_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	printf("Enter the dividend:\n");
	scanf("%s",a);
	printf("Enter the divisor:\n");
	scanf("%s",b);
	send(sockfd,a,sizeof(a),0);
	send(sockfd,b,sizeof(b),0);
	recv(sockfd,buff,sizeof(buff),0);
	printf("Final data with crc appended: %s\n",buff);
	close(sockfd);
}