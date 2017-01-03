#include <stdio.h> 
#include <fcntl.h> 
#include <sys/ioctl.h> 
#include <sys/socket.h>
#include <net/if.h>
#include <arpa/inet.h>
 
#define ETH_P_ARP 0x0806 
#define MAX_PACK_LEN 2000 
#define ETHER_HEADER_LEN 14 
#define ARPREQUEST 1 
#define ARPREPLY 2 
 
struct arp_struct {/*定义一个arp帧结构*/ 
	u_char dst_mac[6]; 
	u_char src_mac[6]; 
	u_short pkt_type; 
	u_short hw_type; 
	u_short pro_type; 
	u_char hw_len; 
	u_char pro_len; 
	u_short arp_op; 
	u_char sender_eth[6]; 
	u_char sender_ip[4]; 
	u_char target_eth[6]; 
	u_char target_ip[4]; 
}; 
union { 
	u_char full_packet[MAX_PACK_LEN]; 
	struct arp_struct arp_pkt; 
}arp;

char * GetMacAddr (u_char * s);
 
void main (int argc, char **argv) 
{ 
	int rec; 
	int len, from_len, rsflags; 
	struct ifreq if_data; 
	struct sockaddr from; 
	u_int8_t MAC[6]; 
	u_int32_t IP, NETMASK, BROADCAST, ip, dip, sip;  
	if (argc != 2) 
	{ 
		fprintf(stderr,"Usage: %s eth0\\n", argv[0]); 
		exit (0); 
	} 
	if ((rec = socket (AF_INET, SOCK_PACKET, htons(ETH_P_ARP))) < 0) 
	{ 
		exit (0); 
	}  
	strcpy (if_data.ifr_name, argv[1]);
	/*获取本机的一些网卡信息*/ 
	if (ioctl (rec, SIOCGIFHWADDR, &if_data) < 0) {  
		exit(1); 
	} 
	memcpy (MAC, if_data.ifr_hwaddr.sa_data, 6); 
	printf ("> My HW Addr: %s\\n", GetMacAddr (MAC)); 
	if (ioctl (rec, SIOCGIFADDR, &if_data) < 0) { 
		exit(1); 
	} 
	memcpy ((void *) &ip, (void *) &if_data.ifr_addr.sa_data + 2, 4); 
	IP = ntohl (ip); 
	printf ("> My IP Addr: %s\\n", inetaddr(ip)); 
	if (ioctl (rec, SIOCGIFNETMASK, &if_data) < 0) 
		perr ("can't get NETMASK addres of my interface!\\n"); 
	memcpy ((void *) &ip, (void *) 
		&if_data.ifr_netmask.sa_data + 2, 4); 
	NETMASK = ntohl (ip); 
	printf ("> My NETMASK: %s\\n", inetaddr(ip)); 
	if (ioctl (rec, SIOCGIFBRDADDR, &if_data) < 0) 
		perr ("can't get BROADCAST addres of my interface!\\n"); 

	memcpy ((void *) &ip, (void *)&if_data.ifr_broadaddr.sa_data + 2, 4); 
	BROADCAST = ntohl (ip); 
	printf ("> My BROADCAST: %s\\n", inetaddr(ip)); 
	if ((rsflags = fcntl (rec, F_GETFL)) == -1) 
	{ 
		perror ("fcntl F_GETFL"); 
		exit (1); 
	} 
	if (fcntl (rec, F_SETFL, rsflags | O_NONBLOCK) == -1) 
	{ 
		perror ("fcntl F_SETFL"); 
		exit (1); 
	}
	/*检测运行Sniffer程序的计算机*/ 
	printf ("> Scanning ....\\n"); 
	for (dip = (IP & NETMASK) + 1; dip < BROADCAST;dip++) 
	{ 
		bzero(arp.full_packet, MAX_PACK_LEN); 
		memcpy (arp.arp_pkt.dst_mac, "\\255\\255\\255\\255\\255\\0", 6); /*ff:ff:ff:ff:ff:00*//* Only change this line! */ 
		memcpy (arp.arp_pkt.src_mac, MAC, 6); 
		arp.arp_pkt.pkt_type = htons( ETH_P_ARP );/*填充发送的试探帧*/ 
		arp.arp_pkt.hw_type = htons( 0x0001 ); 
		arp.arp_pkt.hw_len = 6; 
		arp.arp_pkt.pro_type = htons( 0x0800 ); 
		arp.arp_pkt.pro_len = 4; 
		arp.arp_pkt.arp_op = htons (ARPREQUEST); 
		memcpy (arp.arp_pkt.sender_eth, MAC, 6); 
		ip = htonl (IP); 
		memcpy (arp.arp_pkt.sender_ip, &ip, 4); 
		memcpy (arp.arp_pkt.target_eth, "\\0\\0\\0\\0\\0\\0", 6); 
		ip = htonl (dip); 
		memcpy (arp.arp_pkt.target_ip, &ip, 4); 
		strcpy(from.sa_data, argv[1]); 
		from.sa_family = 1; 
		if( sendto (rec, arp.full_packet, sizeof (struct arp_struct), 0, &from, sizeof(from)) < 0) 
			perror ("sendto"); 
		usleep (50);
		/*如果有恢复证明该主机的网卡处于混乱模式*/ 
		len = recvfrom (rec, arp.full_packet, MAX_PACK_LEN, 0, &from, &from_len); 
		if (len <= ETHER_HEADER_LEN) 
			continue; 
		memcpy (&ip, arp.arp_pkt.target_ip, 4); 
		memcpy (&sip, arp.arp_pkt.sender_ip, 4);
		/*获取网卡处于混乱模式主机信息*/ 
		if (ntohs (arp.arp_pkt.arp_op) == ARPREPLY && ntohl (ip) == IP && ( dip - ntohl(sip) >= 0 ) && ( dip - ntohl(sip) <= 2 ) ) 
		{ 
			printf ("*> Host %s, %s **** Promiscuous mode detected !!!\n", inetaddr (sip), GetMacAddr (arp_pkt.sender_eth)); 
		} 
	} 
	printf ("> End.\\n"); 
	exit (0); 
} 

char * GetMacAddr (u_char * s) 
{ 
	static char buf[30];/*转换MAC地址*/ 
	sprintf (buf, "%02X:%02X:%02X:%02X:%02X:%02X", s[0], s[1], s[2], s[3], s[4], s[5]); 
	return buf; 
}
