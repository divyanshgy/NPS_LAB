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
	struct sockaddr_in server_addr,c_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(myport);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(server_addr.sin_zero,'\0',sizeof(server_addr.sin_zero));

	bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	listen(sockfd,10);

	printf("The server is ready for listening...");
	int size=sizeof(struct sockaddr);
	int afd=accept(sockfd,(struct sockaddr*)&c_addr,&size);

	printf("Port number: %d",myport);
	printf("Connection accepted, ip address:%s (socket %d)\n",inet_ntoa(c_addr.sin_addr),afd);
	close(sockfd);
	close(afd);
}