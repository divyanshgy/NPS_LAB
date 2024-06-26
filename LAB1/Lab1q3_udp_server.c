#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define myport 1500
int main(){
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server_addr,c_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(myport);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(&(server_addr.sin_zero),'\0',sizeof(server_addr.sin_zero));

	bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	printf("Waiting to receive.\n");

	int size=sizeof(struct sockaddr);
	printf("Port number:%d\n",myport);
	printf("Data received from %s: %d(socket %d)\n",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port),sockfd);
	close(sockfd);
}