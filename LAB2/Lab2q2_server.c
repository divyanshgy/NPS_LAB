#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define myport 1388
void swap(char* x,char* y){
	char temp;
	temp=*x;
	*x=*y;
	*y=temp;
}
void permute(char* a,int l, int r){
	int i;
	if (l==r){
		printf("%s\n",a);
	}
	else{
		for (i=l;i<=r;i++){
			swap((a+l),(a+i));
			permute(a,l+1,r);
			swap((a+l),(a+i));
		}
	}
}
int main(){
	int sockfd,size;
	char str[30];
	struct sockaddr_in serv_addr, c_addr;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	size=sizeof(c_addr);
	bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	while(1){
		recvfrom(sockfd,str,sizeof(str),0,(struct sockaddr*)&c_addr,&size);
		printf("\nMessage Recieved: ");
    	printf("%s",str);
    	if (strcmp(str,"stop")==0){
    		break;
    	}
    	printf("\nPermutations of the string are: \n");
    	int n = strlen(str);
    	permute(str, 0, n - 1);
	}
	close(sockfd);
	return 0;
}