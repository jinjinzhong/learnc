#include "pin.h"
/*globals*/
char sendbuf[BUFSIZE];
int datalen;	/*bytes of data,following ICMP header*/
int nsent=1; 	/*syn num*/
pid_t pid;		/*our PID*/
int sockfd;		/*our raw socket*/
struct sockaddr_in to;
struct sockaddr_in from;
int spackets=0;
int rpackets=0;
/*计算时间差*/
void tv_sub(struct timeval* out,struct timeval* in)
{
	if((out->tv_usec-=in->tv_usec)<0) /*out-=in*/
	{
		--out->tv_sec;
		out->tv_usec+=1000000;
	}
	out->tv_sec-=in->tv_sec;
}
/*取得校验和*/
u_short in_cksum(u_short* addr,int len)
{
	int nleft=len;
	int sum=0;
	u_short* w=addr;
	u_short answer=0;
	while(nleft>1)
	{
		sum+=*w++;
		nleft-=2;
	}
	/*mop up an odd byte,if necessary*/
	if(nleft==1)
	{
		*(u_char *)(&answer)=*(u_char *)w;
		sum+=answer;
	}
	sum=(sum>>16)+(sum&0xffff);
	sum+=(sum>>16);
	answer=~sum;
	return(answer);
}
/*发送icmp报文*/
void send_icmp4()
{
	int len;
	struct icmp* icmp;
	icmp=(struct icmp*) sendbuf;
	icmp->icmp_type=ICMP_ECHO;
	icmp->icmp_code=0;
	icmp->icmp_id=pid;
	icmp->icmp_seq=nsent++;
	if(gettimeofday((struct timeval*)icmp->icmp_data,NULL)<0)
	{
		perror("send icmp4 gettimeofday");
		exit(-1);
	}
	/*fill in packet to 64bytes*/
	char *ndata=sendbuf+16;
	int i=0;
	for(i=0;i<48;i++)
	*ndata++='0';
	datalen=sizeof(struct timeval)+48;
	len=8+datalen;
	icmp->icmp_cksum=0;
	icmp->icmp_cksum=in_cksum((u_short*)icmp,len);
	if(sendto(sockfd,sendbuf,len,0,(struct sockaddr*)&to,sizeof(struct sockaddr))<0)
	{
		perror("sendto");
		exit(-1);
	}
	spackets++;
	return;
}
/*处理icmp报文*/
void proc_icmp4(char* ptr,ssize_t len,struct timeval* tvrecv)
{
	int hlenip,icmplen;
	double rtt;
	struct ip* ip;
	struct icmp* icmp;
	struct timeval* tvsend;
	ip=(struct ip*)ptr;
	hlenip=ip->ip_hl<<2;
	icmp=(struct icmp*)(ptr+hlenip);
	if((icmplen=len-hlenip)<8)
	{
		printf("icmplen errno");
		return;
	}
	if(icmp->icmp_type==ICMP_ECHOREPLY)
	{
		if(icmp->icmp_id!=pid)
		return;
		if(icmplen<16)
		{
			printf("icmplen errno");
			return;
		}
		tvsend=(struct timeval *)&(icmp->icmp_data);
		#ifdef DEBUG
		printf("tvrecv->tv_sec=(%d),tvrecv->tv_usec=(%d)\n",tvrecv->tv_sec,tvrecv->tv_usec);
		printf("tvsend->tv_sec=(%d),tvsend->tv_usec=(%d)\n",tvsend->tv_sec,tvsend->tv_usec);
		#endif
		tv_sub(tvrecv,tvsend);
		rtt=tvrecv->tv_sec*1000.0+tvrecv->tv_usec/1000.0;
		char fromip[255];
		if(inet_ntop(AF_INET,&from.sin_addr.s_addr,fromip,255)==NULL)
		{
			perror("inet_ntop fromip");
			return;
		}
		printf("%d bytes from %s:icmp_type=%d,seq=%u,ttl=%d,rtt=%.3f ms\n",icmplen,fromip,icmp->icmp_type,icmp->icmp_seq,ip->ip_ttl,rtt);
	}
	else
	{
  	char fromip[255];
    if(inet_ntop(AF_INET,&from.sin_addr.s_addr,fromip,255)==NULL)
    {
	    perror("inet_ntop fromip");
	    return;
    }
		printf("!!!!!!!!!!!not reply!!!!!!!!!!!!!!!!!!!!\n");
    printf("%d bytes from %s:icmp_type=%d,seq=%u,ttl=%d\n",icmplen,fromip,icmp->icmp_type,icmp->icmp_seq,ip->ip_ttl);
	}
}
static void s_icmp()
{	
	alarm(1);/*set next SIGALRM raise in the next second*/
	send_icmp4();
	return;/*send signal SIGINT!!*/
}
static void r_int()
{
	double lrate=(1-(double)rpackets/(double)spackets)*100.000;
	printf("send= (%d) packets,recieve= (%d) packets,packets loserate= (%.3f\%)\n",spackets,rpackets,lrate);
	exit(0);
}
int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("usage:ping <ipaddress>\n");
		exit(-1);
	}
	char recvbuf[BUFSIZE];
	socklen_t len=sizeof(struct sockaddr_in);
	bzero(&from,len);
	ssize_t n;
	int bufsz;
	struct timeval tval;
	pid=getpid();
	sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
	setuid(getuid());
	bufsz=60*1024;
	/*set buf to a large size*/
	if(setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&bufsz,sizeof(bufsz))<0)
		perror("setsockopt bufsize,but continue proccess\n");
	to.sin_family=AF_INET;
	struct hostent *pser;
	pser=gethostbyname(argv[optind]);
	if(pser==NULL)
	{
		printf("gethostbyname errno=(%d)\n",h_errno);
		exit(-1);
	}
	to.sin_addr=*((struct in_addr*)pser->h_addr);
	if(signal(SIGALRM,s_icmp)==SIG_ERR)
	{
		perror("set signal function");
	}
	if(signal(SIGINT,r_int)==SIG_ERR)
  {
  	perror("set signal function");
  }
	int cntint=0;
	s_icmp(SIGALRM);
	for(;;)
	{
		n=recvfrom(sockfd,recvbuf,sizeof(recvbuf),0,(struct sockaddr*)&from,&len);
		if(n<0)
		{
			if(errno==EINTR)
			{
				continue;
			}
			else
			{
				perror("recvform err");
				close(sockfd);
				exit(-1);
			}
		}
		rpackets++;
		if(gettimeofday(&tval,NULL)<0)
		{
			perror("recv icmp4 gettimeofday");
			exit(-1);
		}
		proc_icmp4(recvbuf,n,&tval);
	}
	return 0;
}

