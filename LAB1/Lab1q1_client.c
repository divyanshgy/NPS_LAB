#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define myport 1234
int main(){
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if (sockfd==-1){
		printf("Socket creation error");
		exit(0);
	}
	struct sockaddr_in c_addr;
	c_addr.sin_port=htons(myport);
	c_addr.sin_family=AF_INET;
	c_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(c_addr.sin_zero,'\0',sizeof(c_addr.sin_zero));

	int size=sizeof(struct sockaddr);
	connect(sockfd,(struct sockaddr*) &c_addr,sizeof(c_addr));

	int buffer[10];
	int choice, sz, temp;
	int odd[10]={0};
	int even[10]={0};
	int a=0, b=0;

	while(1){
		printf("\n1.Sort in ascending order\n");
		printf("2.Sort in descending order\n");
		printf("3.Split into odd and even arrays\n");
		printf("4.Exit\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
			printf("\nEnter the number of elements: \n");
			scanf("%d",&sz);
			printf("\nEnter the elements: \n");
			for (int i=0;i<sz;i++){
				scanf("%d",&buffer[i]);
			}
			send(sockfd,buffer,sizeof(buffer),0);
			send(sockfd,&sz,sizeof(sz),0);
			send(sockfd,&choice,sizeof(choice),0);
			recv(sockfd,buffer,sizeof(buffer),0);
			printf("\nThe array in ascending order is: \n");
			for (int i=0;i<sz;i++){
				printf("%d ",buffer[i]);
			}
			break;
			case 2:
			printf("\nEnter the number of elements: \n");
			scanf("%d",&sz);
			printf("\nEnter the elements: \n");
			for (int i=0;i<sz;i++){
				scanf("%d",&buffer[i]);
			}
			send(sockfd,buffer,sizeof(buffer),0);
			send(sockfd,&sz,sizeof(sz),0);
			send(sockfd,&choice,sizeof(choice),0);
			recv(sockfd,buffer,sizeof(buffer),0);
			printf("\nThe array in descending order is: \n");
			for (int i=0;i<sz;i++){
				printf("%d ",buffer[i]);
			}
			break;
			case 3:
			printf("\nEnter the number of elements: \n");
			scanf("%d",&sz);
			printf("\nEnter the elements: \n");
			for (int i=0;i<sz;i++){
				scanf("%d",&buffer[i]);
			}
			send(sockfd,buffer,40,0);
			send(sockfd,&sz,4,0);
			send(sockfd,&choice,4,0);

			recv(sockfd,odd,40,0);
			recv(sockfd,&b,4,0);
			recv(sockfd,even,40,0);
			recv(sockfd,&a,4,0);
			printf("\nOdd elements are: \n");
			for (int i=0;i<b;i++){
				printf("%d ",odd[i]);
			}
			printf("\nEven elements are: \n");
			for (int i=0;i<a;i++){
				printf("%d ",even[i]);
			}
			break;
			case 4:
			send(sockfd,buffer,40,0);
			send(sockfd,&sz,4,0);
			send(sockfd,&choice,4,0);
			close(sockfd);
			exit(0);
		}
	}
}