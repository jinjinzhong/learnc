#include "in.h"
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#define BUFSIZE 1500

extern char* optarg;
extern int optind,opterr,optopt;
extern int h_errno;/*gethostbyname errno*/
