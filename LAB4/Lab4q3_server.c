#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define myport 1388
int main(){
	int sockfd,afd,size;
	int buff[30],str[30];
	int c1,c2,c3,c,i;
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
		printf("Received data: \n");
		for (i=0;i<strlen(buff);i++){
			printf("%d",buff[i]);
		}
		c1=buff[6]^buff[4]^buff[2]^buff[0];
		c2=buff[5]^buff[4]^buff[1]^buff[0];
		c3=buff[3]^buff[2]^buff[1]^buff[0];
		c=c3*4+c2*2+c1;
		if (c==0){
			printf("\nNo error in transmission\n");
		}else{
			printf("\nError on position %d",c);
			if (buff[c-1]==1){
				buff[c-1]=0;
			}
			else buff[c-1]=1;
			printf("Corrected data: \n");
			for (i=0;i<strlen(buff);i++){
				printf("%d",buff[i]);
			}
		}
		close(afd);
	}
	close(sockfd);
}