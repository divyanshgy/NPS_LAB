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
	struct sockaddr_in dest_addr;
	
	dest_addr.sin_family=AF_INET;
	dest_addr.sin_port=htons(myport);
	dest_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(dest_addr.sin_zero, '\0', sizeof(dest_addr.sin_zero));
	
	connect(sockfd,(struct sockaddr*)&dest_addr,sizeof(struct sockaddr));
	char buffer[30];
	char reply[30];
	int pid=fork();
	
	while(1){
		if (pid==0)
		{
			printf("Enter your message\n");
			scanf("%s",buffer);
			if (strcmp(buffer,"BYE")==0){
				break;
			}
			send(sockfd,buffer,30,0);
		}
		else{
			recv(sockfd,reply,30,0);
			printf("\nServer's Reply:%s",reply);
		}
	}
	int x;
	scanf("%d",&x);
	close(sockfd);
	return 0;
}