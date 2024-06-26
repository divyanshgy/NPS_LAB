#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#define myport 1390
int main(){
	int sockfd, acptfd;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_addr,client_addr;
	char buffer[30];
	char reply[30];
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(myport);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
	
	bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	listen(sockfd,10);
	printf("the server is ready for chatting\n");
	int size=sizeof(struct sockaddr);
	acptfd=accept(sockfd,(struct sockaddr*)&client_addr,&size);
	
	int pid=fork();
	
	while(1){
		if (pid==0)
		{
			recv(acptfd,buffer,30,0);
			printf("Client's message: %s\n",buffer);
		}
		else{
			printf("Enter your reply:\n");
			scanf("%s",reply);
			if (strcmp(reply,"BYE")==0){
				break;
			}
			send(acptfd,reply,30,0);
		}
	}
	close(sockfd);
	printf("Closing the socket\n");
	return 0;
}
