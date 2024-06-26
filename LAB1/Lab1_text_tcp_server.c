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
	struct sockaddr_in server_addr,c_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(myport);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(server_addr.sin_zero,'\0',sizeof(server_addr.sin_zero));

	bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	listen(sockfd,1);

	int size=sizeof(c_addr);
	int new_sockfd=accept(sockfd,(struct sockaddr*)&c_addr,&size);

	for (i=0;;i++){
		recv(new_sockfd,buff,sizeof(buff),0);
		if (buff[0]=='s' && buff[1]=='t' && buff[2]=='o' && buff[3]=='p'){
			break;
		}
		printf("%s\n",buff);
		scanf("%s",buff);
		buff[strlen(buff)]='\0';
		int s=strlen(buff)*sizeof(char);
		send(new_sockfd,buff,s,0);
		if (buff[0]=='s' && buff[1]=='t' && buff[2]=='o' && buff[3]=='p'){
			break;
		}

	}
	close(sockfd);
	close(new_sockfd);

}