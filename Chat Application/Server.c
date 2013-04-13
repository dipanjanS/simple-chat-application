#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
main(int c,char *v[])
{
 int sockfd,newsockfd;
 int clilen,n1,arr[100];
 struct sockaddr_in cli_addr,serv_addr;
 int i;
 char buf[100];
 if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
 {
  printf("Cannot create socket\n");
  exit(0);
}

serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=INADDR_ANY;
serv_addr.sin_port=htons(atoi(v[1]));

 printf("\nStarting Server");
if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
{
 printf("Unable to bind local address\n");
 exit(0);
}

 printf("\n Preparing to listen");
 listen(sockfd,5);
 clilen=sizeof(cli_addr);
 newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
 if(newsockfd < 0)
 {
  printf("Accept error\n");
  exit(0);
}

while(1)
{
 memset(buf,'\0',100);
 printf("Enter the chat message :");
 gets(buf);
 send(newsockfd,buf,100,0);
if(strcmp(buf,"bye")==0)
{
close(newsockfd);
exit(0);
}
 memset(buf,'\0',100);
 recv(newsockfd,buf,100,0);
 printf("%s\n",buf);
 if(strcmp(buf,"bye")==0)
 {
close(newsockfd);
exit(0);
}
}
close(newsockfd);
exit(0);
}
