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
	char a[30],b[30],c[30],enc[30];
	int i,n,j;
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
		recv(afd,a,sizeof(a),0);
		recv(afd,b,sizeof(b),0);
		printf("Dividend: %s\n", a);
		printf("Divisor: %s\n", b);
		strcpy(c,a);
		n=strlen(b);
		for (i=0;i<n-1;i++){
			strcat(c,"0");
		}
		printf("Dividend with zero appended: %s\n",c);
		strcpy(enc,a);

		for(i=0;i<=(strlen(enc))-n;){
			for(j=0;j<n;j++){
				enc[i+j]=enc[i+j]==b[j] ? '0':'1';
			}
			for (;i<strlen(enc) && enc[i]!='1';i++);
		}
		// char temp[30];
		// for (i=strlen(enc)-n+1;i!='\0';i++){
		// 	strcat(temp,enc[i]);
		// }
		// temp[strlen(temp)]='\0';
		char temp[30];
		for (i = strlen(enc) - n + 1; i < strlen(enc); i++) {
    		temp[i - (strlen(enc) - n + 1)] = enc[i];
		}
		temp[i - (strlen(enc) - n + 1)] = '\0';

		char buff[30]="";
		strcat(buff,temp);
		buff[strlen(buff)]='\0';
		printf("%s",buff);
		send(afd,buff,sizeof(buff),0);
		close(afd);
	}

	close(sockfd);
}