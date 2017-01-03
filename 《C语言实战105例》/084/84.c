#include <stdio.h> 
#include <sys/types.h> 
#include <sys/param.h> 
#include <sys/ioctl.h> 
#include <sys/socket.h> 
#include <net/if.h> 
#include <netinet/in.h> 
#include <net/if_arp.h> 
#define MAXINF 16 
int main (int argc, char *argv[]) 
{ 
	int fd, InterfaceNum; 
	struct ifreq buf[MAXINF]; 
	struct arpreq arp; 
	struct ifconf ifc; 
	/*创建套接字*/
	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) >= 0) 
	{ 
		/*初始化结构ifc*/
		ifc.ifc_len = sizeof buf; 
		ifc.ifc_buf = (caddr_t) buf; 
		/*获得所有接口列表*/
		if (!ioctl (fd, SIOCGIFCONF, (char *) &ifc)) 
		{ 
			InterfaceNum = ifc.ifc_len / sizeof (struct ifreq); 
			printf("There are %d interfaces in the host\n\n",InterfaceNum); 
			while (InterfaceNum-- > 0) 
			{ 
				/*输出设备名*/
				printf ("device name ：%s\n", buf[InterfaceNum].ifr_name); 
				/*获得接口标志*/ 
				if (!(ioctl (fd, SIOCGIFFLAGS, (char *) &buf[InterfaceNum])))
				{ 
					if (buf[InterfaceNum].ifr_flags & IFF_PROMISC) 
						printf ("the interface is PROMISC\n"); 
					if (buf[InterfaceNum].ifr_flags & IFF_UP) 
						printf("the interface status is UP\n"); 
					else 
						printf("the interface status is DOWN\n");
				}  
				/*获得IP地址 */ 
				if (!(ioctl (fd, SIOCGIFADDR, (char *) &buf[InterfaceNum]))) 
				{ 
					printf("IP address is:");
					printf("%s\n",inet_ntoa(((struct sockaddr_in*)(&buf[InterfaceNum].ifr_addr))->sin_addr));	
				} 
				/*获取MAC地址 */ 
				if (!(ioctl (fd, SIOCGIFHWADDR, (char *) &buf[InterfaceNum]))) 
				{ 
					printf("MAC address is:"); 
					printf("%02x:%02x:%02x:%02x:%02x:%02x\n", 
					(unsigned char)buf[InterfaceNum].ifr_hwaddr.sa_data[0], 
					(unsigned char)buf[InterfaceNum].ifr_hwaddr.sa_data[1], 
					(unsigned char)buf[InterfaceNum].ifr_hwaddr.sa_data[2], 
					(unsigned char)buf[InterfaceNum].ifr_hwaddr.sa_data[3], 
					(unsigned char)buf[InterfaceNum].ifr_hwaddr.sa_data[4], 
					(unsigned char)buf[InterfaceNum].ifr_hwaddr.sa_data[5]); 
				}
			} 
		} 
	}
	/*关闭套接字*/
	close (fd); 
	return 1; 
}
