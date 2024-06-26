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
	struct sockaddr_in server_addr,c_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(myport);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(&(server_addr.sin_zero),'\0',sizeof(server_addr.sin_zero));

	bind(sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr));
	printf("Waiting to receive.\n");
	char buffer[20];
	int size=sizeof(struct sockaddr);
	int len=0,i,j;
	while(1){
		recvfrom(sockfd,buffer,20,0,(struct sockaddr*)&c_addr,&size);
		if (strcmp(buffer,"Halt")==0){
			close(sockfd);
			exit(0);
		}
		len=strlen(buffer);
		int a=0,e=0,i=0,o=0,u=0;
		char revbuf[20];
		char result[20];
		int j=len-1;
		for (int i=0;i<len;i++){
			switch(buffer[i]){
				case 'a':
				case 'A':
				a++;
				break;
				case 'e':
				case 'E':
				e++;
				break;
				case 'i':
				case 'I': 
				i++; 
				break;
				case 'o':
				case 'O':
				o++; 
				break;
				case 'u':
				case 'U': 
				u++; 
				break;
			}
		}
		for (int i=0;i<len;i++){
			revbuf[j]=buffer[i];
			j--;
		}
		if (strcmp(revbuf,buffer)==0){
			strcpy(result,"Palindrome");
		}
		else{
			strcpy(result,"Not a Palindrome");
		}
		sendto(sockfd,result,sizeof(result),0,(struct sockaddr*)&c_addr,size);
		sendto(sockfd,&len,sizeof(len),0,(struct sockaddr*)&c_addr,size);
		sendto(sockfd,&a,sizeof(a),0,(struct sockaddr*)&c_addr,size);
		sendto(sockfd,&e,sizeof(e),0,(struct sockaddr*)&c_addr,size);
		sendto(sockfd,&i,sizeof(i),0,(struct sockaddr*)&c_addr,size);
		sendto(sockfd,&o,sizeof(o),0,(struct sockaddr*)&c_addr,size);
		sendto(sockfd,&o,sizeof(u),0,(struct sockaddr*)&c_addr,size);
	}
	close(sockfd);
	return 0;
}