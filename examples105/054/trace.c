#include "trace.h"
/*globals*/
char recvbuf[BUFSIZE];
char sendbuf[BUFSIZE];
char *host;
int datalen;/*bytes of data,following ICMP header*/
u_short sport,dport=32768+666;
int nsent;
pid_t pid;
int probe,nprobes=3;
int sendfd,recvfd;
struct sockaddr_in sarecv,salast;
int ttl,max_ttl=30;
int verbose=0;

int recv_v4(int,struct timeval*);
static void sig_alrm(int);
void traceloop(void);
void tv_sub(struct timeval*,struct timeval*);
int sock_cmp_addr(struct sockaddr_in,struct sockaddr_in);

int main(int argc,char** argv)
{
	int c;
	struct addrinfo* ai;
	opterr=0; /*don't want getopt() writing to stderr*/
	struct hostent *pser;
	char ip[255];
	if(argc!=2)
	{
		printf("usage:traceroute [-m<maxttl>-v]<hostname>\n");
		exit(-1);
	}
  pser=gethostbyname(argv[1]);
  if(pser==NULL)
  {
    printf("gethostbyname errno=(%d)\n",h_errno);
    exit(-1);
  }
	host=pser->h_addr;
	/*pointout:gethostbyname return ip is netbyte order NBO!!!*/
  /*no needs to exchange to NBO!!*/
	datalen=sizeof(struct rec);
	pid=getpid();
	if(signal(SIGALRM,sig_alrm)==SIG_ERR)
	  perror("set signal function");
	if((inet_ntop(AF_INET,host,ip,sizeof(ip)))==NULL)//44
	{
		perror("inet_ntop");
		exit(-1);
	}
	printf("tracert to %s,%d hops max,%d data bytes\n",ip,max_ttl,datalen);
	traceloop();
	exit(0);
}
void sock_set_port(struct sockaddr_in* addr,short port)
{
	addr->sin_port=htons(port);
	return;
}
void traceloop(void)
{
	int seq,code,done;
	double rtt;
	struct rec* rec;
	struct sockaddr_in addrme,addrto;
	struct timeval tvrecv;
	char rip[255];
	int e;
	recvfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
	if(recvfd<0)
	{
		perror("creat recvfd");
		exit(-1);
	}
	setuid(getuid());
	sendfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sendfd<0)
	{
		perror("creat sendfd");
		exit(-1);
	}
	addrme.sin_family=AF_INET;
	addrme.sin_addr.s_addr=htonl(INADDR_ANY);
	sport=(getpid()&0xffff)|0x8000;
	sock_set_port(&addrme,sport);/*each proccess works on separate port*/
	addrto.sin_family=AF_INET;
	addrto.sin_addr=*(struct in_addr*)host;
	int on=1;
	if(setsockopt(sendfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0)
	{
		perror("setsockopt\n");
		exit(-1);
	}
	if(bind(sendfd,(struct sockaddr*)&addrme,sizeof(addrme))<0)
	{	e=errno;
		printf("%d",e);
		perror("sendfd bind error");
		exit(-1);
	}
	seq=0;
	done=0;
	
	bzero(&salast,sizeof(salast));
	for(ttl=1;ttl<=max_ttl&&done==0;ttl++)
	{	/*for1 beg*/
		/*set ip ttl*/
		if(setsockopt(sendfd,IPPROTO_IP,IP_TTL,&ttl,sizeof(int))<0)
		{
			perror("setsockopt ttl");
			exit(-1);
		}
		printf("%2d",ttl);
		fflush(stdout);
		for(probe=0;probe<nprobes;probe++)
		{/*for2 beg*/
			rec=(struct rec*)sendbuf;
			rec->rec_seq=++seq;
			rec->rec_ttl=ttl;
			if(gettimeofday(&rec->rec_tv,NULL)<0)
			{
				perror("gettimeofday");
				exit(-1);
			}
			sock_set_port(&addrto,(dport+seq));
			datalen=sizeof(&rec);
			if(sendto(sendfd,sendbuf,datalen,0,(struct sockaddr*)&addrto,sizeof(addrto))<0)
			{
				perror("sendto");
				exit(-1);
			}
			if((code=recv_v4(seq,&tvrecv))==-3)
				printf("*"); /*timeout,no reply*/
			else
			{
				if(sock_cmp_addr(sarecv,salast)!=0)
				{
					if(inet_ntop(AF_INET,&sarecv.sin_addr.s_addr,rip,sizeof(rip))==NULL)
					{
						perror("inet_ntop sarecv:");
						exit(-1);
					}
					printf("from ip:%s ",rip);
					memcpy(&salast,&sarecv,sizeof(sarecv));
				}
				tv_sub(&tvrecv,&rec->rec_tv);
				rtt=tvrecv.tv_sec*1000.0+tvrecv.tv_usec/1000.0;
				printf("rtt=( %.3f) ms",rtt);
				if(code==-1)/*hit the host*/
				{
					printf("hit the host");
					done++;
				}
				else if(code>=0);
				break;
			}
			fflush(stdout);
	       	}/*for2 end*/
	
		printf("\n");
	}/*for1 beg*/
}
/*
Return: -3 on timeout
        -2 on ICMP time exceeded in transit(callers keeps going)
				>=0return value is some other ICMP unreachable code
*/
int recv_v4(int seq,struct timeval* tv)
{
	int hlen1,hlen2,icmplen;
	socklen_t len;
	ssize_t n;
	struct ip* ip,*hip;
	struct icmp* icmp;
	struct udphdr* udp;
	alarm(3);
	for(;;)
	{ 
		len=sizeof(struct sockaddr_in);
		n=recvfrom(recvfd,recvbuf,sizeof(recvbuf),0,(struct sockaddr*)&sarecv,&len);
		if(n<0)
		{
			if(errno==EINTR)
				return(-3);
			else
			{
				perror("recvfrom err");
				exit(-1);
			}
		}
		gettimeofday(tv,NULL);
		ip=(struct ip*)recvbuf;/*start of IP header*/
		hlen1=ip->ip_hl<<2;
		icmp=(struct icmp*)(recvbuf+hlen1);
		if((icmplen=n-hlen1)<8)
		{
			printf("icmplen=(%d)<8",icmplen);
			exit(-1);
		}
		if(icmp->icmp_type==ICMP_TIMXCEED&&icmp->icmp_code==ICMP_TIMXCEED_INTRANS)
		{
			if(icmplen<8+20+8)
			{
				printf("icmplen=(%d)<8+20+8",icmplen);
				exit(-1);
			}
			hip=(struct ip*)(recvbuf+hlen1+8);/*the ip packet which cause the error fllows the icmp header*/
			hlen2=hip->ip_hl<<2;
			udp=(struct udphdr*)(recvbuf+hlen1+8+hlen2);/*the udp header fllows the ip header*/
			if(hip->ip_p==IPPROTO_UDP&&udp->source==htons(sport)&&udp->dest==htons(dport+seq))
				return(-2);/*hit immitate router*/	
		}
	  else if(icmp->icmp_type==ICMP_DEST_UNREACH)
    {
      if(icmplen<8+20+8)
      {
        printf("icmplen=(%d)<8+20+8",icmplen);
        exit(-1);
      }
      hip=(struct ip*)(recvbuf+hlen1+8);/*the ip packet which cause the error fllows the icmp header*/
      hlen2=hip->ip_hl<<2;
      udp=(struct udphdr*)(recvbuf+hlen1+8+hlen2);/*the udp header fllows the ip header*/
      if(hip->ip_p==IPPROTO_UDP&&udp->source==htons(sport)&&udp->dest==htons(dport+seq))
      {
				if(icmp->icmp_code==ICMP_UNREACH_PORT)
          return(-1);/*hit the destinate*/
				else return(icmp->icmp_code);
      }
		}
	}
}

static void sig_alrm(int signo)
{
	return; /*just interrrupt the recvfrom()*/
}

void tv_sub(struct timeval* out,struct timeval* in)
{
        if((out->tv_usec-=in->tv_usec)<0) /*out-=in*/
        {
                --out->tv_sec;
                out->tv_usec+=1000000;
        }
        out->tv_sec-=in->tv_sec;
}

int sock_cmp_addr(struct sockaddr_in sr,struct sockaddr_in sl)
{
	if((sr.sin_family==sl.sin_family)&&(sr.sin_addr.s_addr==sl.sin_addr.s_addr))
	return 0;
	else return -1;
}
