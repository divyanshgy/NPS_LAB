#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#define myport 1345
int main(){
	char buff[50];
	int i;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in c_addr;
	c_addr.sin_family=AF_INET;
	c_addr.sin_port=htons(myport);
	c_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(c_addr.sin_zero,'\0',sizeof(c_addr.sin_zero));

	connect(sockfd,(struct sockaddr*)&c_addr,sizeof(c_addr));

	for(i=0;;i++){
		//memset(buff,'\0',sizeof(buff));
		printf("Enter the text\n");
		scanf("%s",buff);
		buff[strlen(buff)]='\0';
		int s=strlen(buff)*sizeof(char);
		send(sockfd,buff,s,0);
		if (buff[0]=='s' && buff[1]=='t' && buff[2]=='o' && buff[3]=='p'){
			break;
		}
		//memset(buff,'\0',sizeof(buff));
		recv(sockfd,buff,sizeof(buff),0);
		printf("%s\n",buff);
		if (buff[0]=='s' && buff[1]=='t' && buff[2]=='o' && buff[3]=='p'){
			break;
		}
	}
	close(sockfd);
}