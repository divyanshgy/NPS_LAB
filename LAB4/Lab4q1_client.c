#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#define myport 1388
int main(){
	int sockfd;
	char buff[30];
	int i,n=0;
	struct sockaddr_in serv_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	
	printf("Enter the string:\n");
	scanf("%s",buff);
	for (i=0;i<strlen(buff);i++){
		if (buff[i]=='1'){
			n++;
		}
	}
	if (n%2==0){
		strcat(buff,"1");
	}
	else{
		strcat(buff,"0");
	}
	buff[strlen(buff)+1]='\0';
	send(sockfd,buff,sizeof(buff),0);
	close(sockfd);
}