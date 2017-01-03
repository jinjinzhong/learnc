#ifndef IN_H
#define IN_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<sys/time.h>
#include<sys/types.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<net/if.h>
#include<unistd.h>
#include<errno.h>
#include<math.h>


extern int errno;
inline int max(int a,int b)
{
	return((a>b)?a:b);
}

#endif

