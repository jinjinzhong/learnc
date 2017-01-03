#ifndef _TRACE_H
#define _TRACE_H
#include "in.h"
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>

#define BUFSIZE 1500
struct rec
{
	u_short rec_seq;
	u_short rec_rtt;
	u_short rec_ttl;
	struct timeval rec_tv;
};
#endif
