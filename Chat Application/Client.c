#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
main(int c, char *v[])
{
 int sockfd;
 struct sockaddr_in serv_addr;
 int i,t;
 char buf[100];
 if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
 {
  printf("Unable to create socket\n");
  exit(0);
 }

serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=inet_addr(v[2]);
serv_addr.sin_port=htons(atoi(v[1]));
if((connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)))<0)
{
 printf("Unable to connect to server\n");
 exit(0);
}
while(1)
{
memset(buf,'\0',100);
recv(sockfd,buf,100,0);
printf("%s\n",buf);
if(strcmp(buf,"bye")==0)
break;
memset(buf,'\0',100);
printf("Enter the chat message:");
gets(buf);
send(sockfd,buf,100,0);
if(strcmp(buf,"bye")==0)
break;
}
close(sockfd);
}
