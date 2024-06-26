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
	int sockfd,afd,size;
	char buff[30];
	int i,n=0;
	struct sockaddr_in serv_addr, c_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	listen(sockfd,5);
	
	
	while(1){
		size=sizeof(c_addr);
		afd=accept(sockfd,(struct sockaddr*)&c_addr,&size);

		recv(afd,buff,sizeof(buff),0);
		printf("Received string: \n");
		for (i=0;i<strlen(buff)-1;i++){
			printf("%c",buff[i]);
		}
		for (i=0;i<strlen(buff)-1;i++){
			if (buff[i]=='1'){
				n++;
			}
		}
		if (n%2==0 && buff[strlen(buff)-1]=='1'){
			printf("\nNo Error occured\n");
		}
		else if (n%2==0 && buff[strlen(buff)-1]=='0'){
			printf("\nError occured\n");
		}
		else if (n%2!=0 && buff[strlen(buff)-1]=='0'){
			printf("\nNo Error occured\n");
		}
		else if (n%2!=0 && buff[strlen(buff)-1]=='1'){
			printf("\nError occured\n");
		}
		close(afd);
	}
	close(sockfd);
}