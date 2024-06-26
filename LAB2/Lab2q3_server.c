#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define myport 1388
int main(){
	int sockfd,size,afd;
	char buff[30], str1[30], str2[30];
	struct sockaddr_in serv_addr, c_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	listen(sockfd,5);
	size=sizeof(c_addr);
	afd=accept(sockfd,(struct sockaddr*)&c_addr,&size);
	
	
	recv(afd,buff,sizeof(buff),0);
	printf("\nMessage Recieved: ");
  	printf("%s\n",buff);
	int i,x;
	int j=0,k=0;
	for (i=0;i<strlen(buff);i++){
		if (buff[i]>=48 && buff[i]<=57){
			str1[j]=buff[i];
			j++;
		}
		else{
			str2[k]=buff[i];
			k++;
		}
	}
	str1[j]='\0';
	str2[k]='\0';

	int pid=fork();
	if (pid>0){
		for (i = 0; i < k - 1; i++) 
    	{
    		for (x = 0; x < k - i - 1; x++) 
      		{
       			if (str2[x] < str2[x + 1]) 
       			{
         			char temp = str2[x];
          			str2[x] = str2[x + 1];
          			str2[x + 1] = temp;
        		}
      		}
   		}
   		printf("\nParent process - Sorted alphabetical string is:  \n");
    	printf("%s\n", str2);
    	//send(sockfd, str2, sizeof(str2), 0);
	}
	else 
  	{
    	//child
    	for (i = 0; i < j - 1; i++) 
    	{
     		for (x = 0; x < j - i - 1; x++) 
      		{
        		if (str1[x] > str1[x + 1]) 
        		{
          			char temp = str1[x];
         			str1[x] = str1[x + 1];
          			str1[x + 1] = temp;
        		}
      		}
    	}
    	printf("\nChild process - Sorted numerical string is:  \n");
    	printf("%s\n", str1);
   		//send(sockfd, str1, sizeof(str1), 0);
  	}
	
  	close(afd);
  	close(sockfd);
}