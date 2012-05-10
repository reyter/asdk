// ping.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef	WIN32

#define WIN32_LEAN_AND_MEAN
#include <winsock.h>
#pragma	comment(lib, "Wsock32.lib")

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#endif

#define ICMP_ECHO 8 
#define ICMP_ECHOREPLY 0 

//#define ICMP_MIN 8	// minimum 8 byte icmp packet (just header) 
#define ICMP_MIN (8 + 4)	// minimum 8 byte icmp packet (just header + timestamp)

// IP header
typedef struct _tagX_iphdr
{
	unsigned char	h_len:4;          // length of the header 
	unsigned char	version:4;        // Version of IP 
	unsigned char	tos;             // Type of service 
	unsigned short	total_len;      // total length of the packet 

	unsigned short	ident;          // unique identifier 
	unsigned short	frag_and_flags; // flags 
	
	unsigned char	ttl;				// ttl
	unsigned char	proto;           // protocol (TCP, UDP etc) 
	unsigned short	checksum;       // IP checksum 
	
	unsigned int	sourceIP; 
	unsigned int	destIP; 
}XIpHeader;

// ICMP header
typedef struct _tagX_icmphdr
{
	unsigned char	i_type;
	unsigned char	i_code;
	unsigned short	i_cksum;
	unsigned short	i_id;
	unsigned short	i_seq;
	unsigned long	i_timestamp;
}XIcmpHeader;

//puclic code
//网际校验和生产算法
//网际校验和是被校验数据16位值的反码和(ones-complement sum)
unsigned short in_cksum(unsigned short* addr, int len)
{
	int		nleft = len;
	int		sum = 0;
	unsigned short* w = addr;
	unsigned short answer = 0;
	
	while(nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}

	if(nleft == 1) {
		*(unsigned char*)(&answer) = *(unsigned char*)w;
		sum += answer;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;

	return (answer);
}

void fill_IpHeader(char *buf)
{
//	XIpHeader *ip_hdr = (XIpHeader *)buf;
}

void fill_IcmpData(char *buf, int datasize)
{
	if (buf)
	{
		char ch = 0;
		char* icmpdata = buf + sizeof(XIcmpHeader);
		fprintf(stdout, "(IcmpData)\r\n");
		for (int i = 0; i < datasize; i++)
		{
			ch = 'A' + i%('z' - 'A');
			*(icmpdata + i) = ch;
			fprintf(stdout, "%c", ch);
		}
		fprintf(stdout, "\r\n");
	}
}

void fill_IcmpHeader(char *buf, int datasize)
{
	static unsigned short seq_no = 0;
	XIcmpHeader *icmp_hdr = (XIcmpHeader *)buf;
	if (icmp_hdr)
	{
		icmp_hdr->i_type = ICMP_ECHO;
		icmp_hdr->i_code = 0;
		icmp_hdr->i_cksum = 0;

#ifdef	WIN32
		icmp_hdr->i_id = (unsigned short)GetCurrentProcessId(); 
#else
		icmp_hdr->i_id = (unsigned short)getpid(); 
#endif
		icmp_hdr->i_seq = seq_no++;

#ifdef	WIN32
		icmp_hdr->i_timestamp = (unsigned long)::GetTickCount();
#else
		icmp_hdr->i_timestamp = (unsigned long)time(NULL);
#endif

		icmp_hdr->i_cksum = in_cksum((unsigned short*)buf, sizeof(XIcmpHeader) + datasize);

		fprintf(stdout, "(IcmpHeader)\r\n");
		fprintf(stdout, "%02X%02X%04X\r\n", icmp_hdr->i_type, icmp_hdr->i_code, icmp_hdr->i_cksum);
		fprintf(stdout, "%04X%04X\r\n", icmp_hdr->i_id, icmp_hdr->i_seq);
		fprintf(stdout, "%08X\r\n", icmp_hdr->i_timestamp);
	}
}

// decode
void decode_IpIcmp(char *buf, int size)
{
	XIpHeader *ip_hdr = (XIpHeader *)buf;
	unsigned short iphdrlen;
	if (ip_hdr)
	{
		fprintf(stdout, "(IpHeader)\r\n");
		fprintf(stdout, "%01X%01X%02X%04X\r\n", ip_hdr->version, ip_hdr->h_len, ip_hdr->tos, ip_hdr->total_len);
		fprintf(stdout, "%04X%04X\r\n", ip_hdr->ident, ip_hdr->frag_and_flags);
		fprintf(stdout, "%02X%02X%04X\r\n", ip_hdr->ttl, ip_hdr->proto, ip_hdr->checksum);

		//iphdrlen = ip_hdr->h_len * 4; // number of 32-bit words *4 = bytes
		iphdrlen = ip_hdr->h_len << 2; // number of 32-bit words *4 = bytes
		fprintf(stdout, "(IcmpHeader)\r\n");
		if (size < iphdrlen + ICMP_MIN)
		{
			fprintf(stdout, "Reply %d bytes Too few\r\n", size);
		}
		else
		{
			XIcmpHeader *icmp_hdr = (XIcmpHeader *)(buf + iphdrlen);

			fprintf(stdout, "%02X%02X%04X\r\n", icmp_hdr->i_type, icmp_hdr->i_code, icmp_hdr->i_cksum);
			fprintf(stdout, "%04X%04X\r\n", icmp_hdr->i_id, icmp_hdr->i_seq);
			fprintf(stdout, "%08X\r\n", icmp_hdr->i_timestamp);
/*			
			fprintf(stdout, "(IcmpData)\r\n");
			int iIcmpDataSize = size - iphdrlen - sizeof(XIcmpHeader);
			char *icmpdata = buf + iIcmpDataSize;
			for (int i = 0; i < iIcmpDataSize; i++)
				fprintf(stdout, "%c", *(icmpdata + i));
			fprintf(stdout, "\r\n");
*/
			unsigned long timestamp = 0;
#ifdef	WIN32
			timestamp = (unsigned long)::GetTickCount();
#else
			timestamp = (unsigned long)time(NULL);;
#endif
			timestamp -= icmp_hdr->i_timestamp;

			struct sockaddr_in from;
			from.sin_addr.s_addr = ip_hdr->sourceIP;

			fprintf(stdout, "Reply %d bytes from: %s time<%d TTL=%d icmp_seq=%d\r\n",
				size,
				inet_ntoa(from.sin_addr),
				timestamp,
				ip_hdr->ttl,
				icmp_hdr->i_seq
				);
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	int	ret = 0;
	system("pause");
#ifdef	WIN32
	WSADATA ws;
	WSAStartup(0x0101,&ws);
	//#else
	//	;
#endif

	int iIcmpDataSize = 0;
	struct sockaddr_in dest,from;
	unsigned int addr = 0;
	struct hostent *hp;

	char buffer[1024];
	char recv_buffer[1024];

	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s [host|ip] [datasize]\r\n", argv[0]);
		return 0;
	}

	if (argc > 2)
		iIcmpDataSize = atoi(argv[2]);
	if (iIcmpDataSize < 1 || iIcmpDataSize > 1024)
		iIcmpDataSize = 10;

	memset(&dest, 0, sizeof dest);
	dest.sin_family = AF_INET;
	hp = gethostbyname(argv[1]);
	if (!hp)
		addr = inet_addr(argv[1]);
	if ((!hp) && (addr == INADDR_NONE))
	{
		fprintf(stderr,"Unable to resolve %s\r\n",argv[1]);
		return 0;
	}
	if (hp != NULL)
		memcpy(&(dest.sin_addr), hp->h_addr,hp->h_length);
	else
		dest.sin_addr.s_addr = addr;

#ifdef	WIN32
	//	;
#else
	setuid(getuid());
	//	setuid(0);
#endif
	int sockfd;
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	fprintf(stdout, "XPing...\r\n");
	for (int i = 0; i < 10; i++)
	{
		fprintf(stdout, "Echo...\r\n");
		memset(buffer, 0, 1024);
		fill_IcmpData(buffer, iIcmpDataSize);
		fill_IcmpHeader(buffer, iIcmpDataSize);
		XIcmpHeader *icmp_hdr = (XIcmpHeader *)buffer;
		int iSendSize = sendto(sockfd, buffer, sizeof(XIcmpHeader) + iIcmpDataSize, 0, (struct sockaddr*)&dest, sizeof(dest));

		fprintf(stdout, "Reply...\r\n");
		memset(&from, 0, sizeof from);
		memset(recv_buffer, 0, 1024);
#ifdef	WIN32
		int fromlen = sizeof(from);
		int iRecvSize = recvfrom(sockfd, recv_buffer, 1024, 0, (struct sockaddr*)&from,  &fromlen);
#else
		socklen_t fromlen = sizeof(from);
		int iRecvSize = recvfrom(sockfd, recv_buffer, 1024, 0, (struct sockaddr*)&from,  &fromlen);
#endif
		if (iRecvSize > 0)
			decode_IpIcmp(recv_buffer, iRecvSize);
	}

#ifdef	WIN32
	WSACleanup();
	//#else
	//	;
#endif

	return ret;
}

