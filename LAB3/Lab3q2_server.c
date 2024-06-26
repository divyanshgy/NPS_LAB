#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define myport 1388

int find_anagram(char str1[],char str2[]){
	int num1[26]={0},num2[26]={0};
	int i=0;
	while(str1[i]!='\0'){
		num1[str1[i]-'a']++;
		i++;
	}
	i=0;
	while(str2[i]!='\0'){
		num2[str2[i]-'a']++;
		i++;
	}
	for (i = 0; i < 26; i++)
    {
        if (num1[i] != num2[i])
            return 0;
    }
    return 1;
}
int main(){
	int sockfd,afd;
	struct sockaddr_in serv_addr,c_addr;
	char buff[50],buff2[50],buff1[50];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	listen(sockfd,5);
	int size;

	while(1){
		size=sizeof(c_addr);
		afd=accept(sockfd,(struct sockaddr*)&c_addr,&size);
		recv(afd,buff,sizeof(buff),0);
		printf("Socket address is: %s\n",buff);	

		recv(afd,buff1,sizeof(buff1),0);
		
		printf("\nString 1 Recieved: ");
		printf("%s\n", buff1);

		recv(afd,buff2,sizeof(buff2),0);
	
		printf("\nString 2 Recieved: ");
		printf("%s\n", buff2);
		int flag = find_anagram(buff1, buff2);
    	if (flag == 1)
        	strcpy(buff,"Strings are anagrams");
    	else
        	strcpy(buff,"Strings are not anagrams");

		send(afd,buff,sizeof(buff),0);
		close(afd);
	}
	close(sockfd);
}