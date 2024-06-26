#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#define myport 1390
int main(){
	int i;
	char buff[50];
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in c_addr;
	c_addr.sin_family=AF_INET;
	c_addr.sin_port=htons(myport);
	c_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(c_addr.sin_zero,'\0',sizeof(c_addr.sin_zero));

	for (i=0;;i++){
		printf("Enter the text:\n");
		scanf("%s",buff);
		sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&c_addr,sizeof(c_addr));
		if (buff[0]=='s' && buff[1]=='t' && buff[2]=='o' && buff[3]=='p'){
			break;
		}
		int size=sizeof(c_addr);
		recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&c_addr,&size);
		printf("%s\n",buff);
		if (buff[0]=='s' && buff[1]=='t' && buff[2]=='o' && buff[3]=='p'){
			break;
		}
	}
	close(sockfd);
}