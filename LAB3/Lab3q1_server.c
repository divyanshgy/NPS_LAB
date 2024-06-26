#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define myport 1388
#define MAXLINE 4096
#define LISTENQ 8
int main(){
	int sockfd,afd;
	struct sockaddr_in serv_addr,c_addr;
	char buff[100],str[100];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(myport);
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	listen(sockfd,LISTENQ);
	int childpid;
	int no_of_clients=0;

	while(1){
		int len=sizeof(c_addr);
		afd=accept(sockfd,(struct sockaddr*)&c_addr,&len);

		if (no_of_clients==2){
			printf("\nMore than 2 clients!\n");
			close(afd);
			break;
		}
		no_of_clients++;

		if ((childpid=fork())==0){
			close(sockfd);
		}
		recv(afd,buff,sizeof(buff),0);

		FILE *fptr;
		fptr=fopen("tmp.txt","a");
		fputs(buff,fptr);
		fclose(fptr);

		char buff2[50];
		FILE *fptr2;
		fptr2=fopen("tmp2.txt","a");
		fputs(buff2,fptr2);
		fclose(fptr2);

		if (no_of_clients==2){
			FILE *fp;
			int line_num=1;
			char temp[512];
			if ((fp = fopen("tmp.txt", "r")) == NULL) {
               close(sockfd);
               exit(0);
            }
            while (fgets(temp, 512, fp) != NULL) {
               strcpy(str, temp);
               printf("%s", str);
               line_num++;
            }
            if (fp) {
               fclose(fp);
            }

            FILE *fp2;
            int line_num2 = 1;
            char temp2[512];
            if ((fp2 = fopen("tmp2.txt", "r")) == NULL) {
               close(sockfd);
               exit(0);
            }
            while (fgets(temp2, 512, fp2) != NULL) {
               strcpy(str, temp2);
               printf("\n%s", str);
               line_num2++;
            }
            if (fp2) {
               fclose(fp2);
            }
		}
		exit(0);
	}
	close(afd);
}
