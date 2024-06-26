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
	char str[30];
	struct sockaddr_in serv_addr;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	size=sizeof(serv_addr);
	while(1){
		printf("Enter string (enter 'stop' to exit): ");
    	scanf("%s",str);
    	sendto(sockfd,str,sizeof(str),0,(struct sockaddr*)&serv_addr,size);
    	if (strcmp(str,"stop")==0){
    		break;
    	}
	}
	close(sockfd);
	return 0;
}