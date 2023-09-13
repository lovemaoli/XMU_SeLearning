#define _CRT_SECURE_NO_WARNINGS//忽视部分报错，以便将捕获到的帧写入csv文件
#define HAVE_REMOTE
#define WIN32 //防止引用unix库
#include <pcap.h> // WinPcap内核库
#include <Packet32.h>
#include <ntddndis.h> // Windows DDK驱动程序接口定义
#include <string.h>
#include <iostream>
#include <sstream>
#pragma comment(lib, "Packet")
#pragma comment(lib, "wpcap")
#pragma comment(lib, "WS2_32")

/* 4字节IP地址  */
typedef struct ip_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

/* IPv4 头部 */
typedef struct ip_header
{
	u_char	ver_ihl;		// Version (4 bits) + Internet header length (4 bits)
	u_char	tos;			// Type of service 
	u_short tlen;			// Total length 
	u_short identification; // Identification
	u_short flags_fo;		// Flags (3 bits) + Fragment offset (13 bits)
	u_char	ttl;			// Time to live
	u_char	proto;			// Protocol
	u_short crc;			// Header checksum
	ip_address	saddr;		// Source address
	ip_address	daddr;		// Destination address
	u_int	op_pad;			// Option + Padding
}ip_header;

/* TCP 头部 */
typedef struct tcp_header
{
	u_short sport;	// Source port 源端口号
	u_short dport;	// Destination port 目标端口号
	u_int SEQ;		// Seq 串行号
	u_int ACK;		// Ask 确认号
	u_char len;	    //len 数据偏移量
	u_char sign; // 保留字段
	u_short win_size; // 窗口大小
	u_short mark; // 标记
	u_short point; // 紧急指针
}tcp_header;

/* 捕获到数据包的回调函数 */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);
int pstr_to_int(char* s1, char* s2);
int port = 21; //ftp端口
int main()
{
	pcap_if_t* alldevs;
	pcap_if_t* d;
	int inum;
	int i = 0;
	pcap_t* adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask;
	char packet_filter[] = "tcp";	//设置过滤器为tcp
	struct bpf_program fcode;

	//获取设备列表
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}
	//打印列表
	for (d = alldevs; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}
	printf("Enter the interface number (1-%d):", i);
	scanf("%d", &inum);

	/* Check if the user specified a valid adapter */
	if (inum < 1 || inum > i)
	{
		printf("\nAdapter number out of range.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* Jump to the selected adapter */
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);

	/* Open the adapter */
	if ((adhandle = pcap_open_live(d->name,	// name of the device
		65536,			// portion of the packet to capture. 
		// 65536 grants that the whole packet will be captured on all the MACs.
		1,				// promiscuous mode (nonzero means promiscuous)
		1000,			// read timeout
		errbuf			// error buffer
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}
	if (d->addresses != NULL)
		/* Retrieve the mask of the first address of the interface */
		netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* If the interface is without addresses we suppose to be in a C class network */
		netmask = 0xffffff;

	//编译过滤器
	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}
	//set the filter
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}

	printf("\nlistening on %s...\n", d->description);

	pcap_freealldevs(alldevs);

	/* start the capture */
	pcap_loop(adhandle, 0, packet_handler, NULL);

	return 0;
}

/* libpcap为每个传入数据包调用的回调函数 */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	FILE* file = fopen("data.txt", "a+");
	struct tm* ltime;
	char timestr[16];
	ip_header* ih;
	byte* mac_header;
	tcp_header* th;
	u_int ip_len;
	u_short sport, dport;
	time_t local_tv_sec;
	(VOID)(param);

	/* 将时间戳转换为可读格式 */
	local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

	/* IP头的位置 */
	ih = (ip_header*)(pkt_data + 14); //length of ethernet header

	/* MAC头的位置 */
	mac_header = (byte*)pkt_data;

	/* udp头的位置 */
	ip_len = (ih->ver_ihl & 0xf) * 4;
	th = (tcp_header*)((u_char*)ih + ip_len);

	/* 从网络字节顺序转换为主机字节顺序 */
	sport = ntohs(th->sport);
	dport = ntohs(th->dport);

	/*抓取ftp包 过滤21 and port*/
	if ((sport != 21 && dport != 21) && (sport != port && dport != port))
		return;

	printf("Time:%s.%.6d len:%d \n", timestr, header->ts.tv_usec, header->len);
	/* 打印 MAC and IP */
	printf("DEST MAC %x.%x.%x.%x.%x.%x \n", mac_header[0], mac_header[1], mac_header[2], mac_header[3], mac_header[4], mac_header[5]);
	printf("SRC MAC %x.%x.%x.%x.%x.%x \n", mac_header[6], mac_header[7], mac_header[8], mac_header[9], mac_header[10], mac_header[11]);
	printf("DEST IP:%d.%d.%d.%d\n",
		ih->daddr.byte1,
		ih->daddr.byte2,
		ih->daddr.byte3,
		ih->daddr.byte4
	);
	printf("SRC IP:%d.%d.%d.%d\n",
		ih->saddr.byte1,
		ih->saddr.byte2,
		ih->saddr.byte3,
		ih->saddr.byte4
	);
	printf("TCP.sport:%d\n", sport);
	printf("TCP.dport:%d\n", dport);
	printf("6比特标志位：\n");
	fprintf(file, "Time:%s.%.6d len:%d \n", timestr, header->ts.tv_usec, header->len);
	/* 对应输出文件 */
	fprintf(file, "DEST MAC %x.%x.%x.%x.%x.%x \n", mac_header[0], mac_header[1], mac_header[2], mac_header[3], mac_header[4], mac_header[5]);
	fprintf(file, "SRC MAC %x.%x.%x.%x.%x.%x \n", mac_header[6], mac_header[7], mac_header[8], mac_header[9], mac_header[10], mac_header[11]);
	fprintf(file, "DEST IP:%d.%d.%d.%d\n",
		ih->daddr.byte1,
		ih->daddr.byte2,
		ih->daddr.byte3,
		ih->daddr.byte4
	);
	fprintf(file, "SRC IP:%d.%d.%d.%d\n",
		ih->saddr.byte1,
		ih->saddr.byte2,
		ih->saddr.byte3,
		ih->saddr.byte4
	);
	fprintf(file, "TCP.sport:%d\n", sport);
	fprintf(file, "TCP.dport:%d\n", dport);
	fprintf(file, "6比特标志位：\n");

	u_char s = th->sign;
	unsigned short s1 = 0;//0010 0000,urg
	unsigned short s2 = 0;//0001 0000,ack
	unsigned short s3 = 0;//0000 1000,psh
	unsigned short s4 = 0;//0000 0100,rst
	unsigned short s5 = 0;//0000 0010,syn
	unsigned short s6 = 0;//0000 0001,fin
	if ((s & 32) == 32)//0010 0000
		s1 = 1;
	if ((s & 16) == 16)//0001 0000
		s2 = 1;
	if ((s & 8) == 8)//0000 1000
		s3 = 1;
	if ((s & 4) == 4)//0000 0100
		s4 = 1;
	if ((s & 2) == 2)//0000 0010
		s5 = 1;
	if ((s & 1) == 1)//0000 0001
		s6 = 1;
	printf("URG=%d\tACK=%d\tPSH=%d\tRST=%d\tSYN=%d\tFIN=%d\n", s1, s2, s3, s4, s5, s6);
	fprintf(file, "URG=%d\tACK=%d\tPSH=%d\tRST=%d\tSYN=%d\tFIN=%d\n", s1, s2, s3, s4, s5, s6);
	/*找握手包和挥手包,SYN==1是握手将建立连接，FIN==1是挥手将释放连接*/
	if (s5 == 1) {
		if (s2 == 0) {//000010
			printf("ftp - 第一个握手包\n");
			fprintf(file, "ftp - 第一个握手包\n");
		}
		else { //010010
			printf("ftp - 第二个握手包\n");
			fprintf(file, "ftp - 第二个握手包\n");
		}
	}
	if (s6 == 1) {
		if (dport == 21) { //目的端口号为21
			printf("ftp - 挥手包，客户端向FTP服务端发出\n");
			fprintf(file, "ftp - 挥手包，客户端向FTP服务端发出\n");
		}
		else {
			printf("ftp - 挥手包，FTP服务端向客户端发出\n");
			fprintf(file, "ftp - 挥手包，FTP服务端向客户端发出\n");
		}

	}

	/*服务器与客户端*/
	if (dport == 21 || dport == port) {
		printf("Client--->Server\n");
		fprintf(file, "Server--->Client\n");
	}
	else if (sport == 21 || sport == port) {
		printf("Server--->Client\n");
		fprintf(file, "Server--->Client\n");
	}

	/*数据内容*/
	char tcp_len = (th->len & 240) >> 4; //取字节的前4位,单位为字(4字节)
	if (header->len > 34 + tcp_len * 4) //34是以太网头+IP头长度
	{
		byte* data_header = (byte*)pkt_data;
		/*数据帧*/
		printf("ftp data:");
		fprintf(file, "ftp data:");
		for (int i = 34 + tcp_len * 4; i < header->len; i++) {
			printf("%c", data_header[i]);
			fprintf(file, "%c", data_header[i]);
		}
		/*读取ftp指令*/
		if (sport == 21 || dport == 21) {
			char str[100] = { 0 };

			int j = 0;

			for (int i = 34 + tcp_len * 4; i < header->len; i++) {
				if (data_header[i] == ' ') {
					if (strcmp(str, "USER") == 0) {
						printf("user name:");
						fprintf(file, "user name:");
						for (; i < header->len; i++) {
							printf("%c", data_header[i]);
							fprintf(file, "%c", data_header[i]);
						}
					}
					else if (strcmp(str, "PASS") == 0) {
						printf("password:");
						fprintf(file, "password:");
						for (; i < header->len; i++) {
							printf("%c", data_header[i]);
							fprintf(file, "%c", data_header[i]);
						}
					}
					else if (strcmp(str, "227") == 0) {
						int num = 0;		//Entering Passive Mode取第5位和第6位
						for (; i < header->len; i++) {
							if (num == 4) {
								char s1[10] = { 0 };
								char s2[10] = { 0 };
								int z = 0;
								while (data_header[i] != ',') {
									s1[z] = data_header[i];
									z++;
									i++;
								}
								num++;
								i++;
								z = 0;
								while (data_header[i] != ')') {
									s2[z] = data_header[i];
									z++;
									i++;
								}
								port = pstr_to_int(s1, s2);//修改端口
							}
							if (data_header[i] == ',') {
								num++;
							}
						}
					}
					break;
				}
				str[j++] = data_header[i];
			}

		}
	}
	printf("\n");
	fprintf(file, "\n");
	fclose(file);
}

/*求被动打开时服务器的端口*/
int pstr_to_int(char* s1, char* s2) {
	int n1 = atoi(s1);
	int n2 = atoi(s2);
	return 256 * n1 + n2;
}