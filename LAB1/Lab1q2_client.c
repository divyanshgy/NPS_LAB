#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define myport 1324
int main(){
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	addr.sin_port=htons(myport);
	memset(addr.sin_zero,'\0',sizeof(addr.sin_zero));

	printf("Successful till here\n");
	int size=sizeof(struct sockaddr);
	char buffer[20];
	char result[20];
	int len;
	int a=0, e=0, i=0, o=0, u=0;
	while(1){
		printf("Enter the string: \n");
		scanf("%s",buffer);
		if (strcmp(buffer,"Halt")==0){
			sendto(sockfd,buffer,20,0,(struct sockaddr *)&addr,size);
			printf("Closing the socket(client).");
			close(sockfd);
			exit(0);
		}
		sendto(sockfd,buffer,20,0,(struct sockaddr *) &addr,size);
		recvfrom(sockfd,result,20,0,(struct sockaddr *) &addr,&size);
		recvfrom(sockfd,&len,sizeof(len),0,(struct sockaddr *) &addr,&size);
		recvfrom(sockfd,&a,sizeof(a),0,(struct sockaddr *) &addr,&size);
		recvfrom(sockfd,&e,sizeof(e),0,(struct sockaddr *) &addr,&size);
		recvfrom(sockfd,&i,sizeof(i),0,(struct sockaddr *) &addr,&size);
		recvfrom(sockfd,&o,sizeof(o),0,(struct sockaddr *) &addr,&size);
		recvfrom(sockfd,&u,sizeof(u),0,(struct sockaddr *) &addr,&size);
		printf("\nSize of the string is: %d\n",len);
		printf("Result: %s\n",result);
		printf("Vowels count: \n");
		printf("a: %d\n",a);
		printf("e: %d\n",e);
		printf("i: %d\n",i);
		printf("o: %d\n",o);
		printf("u: %d\n",u);
	}
	return 0;
}