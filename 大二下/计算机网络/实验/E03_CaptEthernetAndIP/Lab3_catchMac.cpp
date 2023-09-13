#define _CRT_SECURE_NO_WARNINGS//忽视部分报错，以便将捕获到的帧写入csv文件
#define HAVE_REMOTE
#define WIN32 //防止引用unix库
#include <pcap.h>
#include <Packet32.h>
#include <ntddndis.h>
#include <string.h>
#pragma comment(lib, "Packet")
#pragma comment(lib, "wpcap")
#pragma comment(lib, "WS2_32")

typedef struct ip_header {//IP帧格式
	u_char ver_ihl; // Version (4 bits) + Internet header length(4 bits)
	u_char tos; // Type of service 
	u_short tlen; // Total length 
	u_short identification; // Identification
	u_short flags_fo; // Flags (3 bits) + Fragment  offset(13 bits)
	u_char ttl; // Time to live
	u_char proto; // Protocol
	u_short crc; // Header checksum
	u_char saddr[4]; // Source address
	u_char daddr[4]; // Destination address
	u_int op_pad; // Option + Padding
} ip_header;

typedef struct mac_header {//以太网数据链路层的帧格式
	u_char dest_addr[6];
	u_char src_addr[6];
	u_char type[2];
} mac_header;

int main()
{
	//定义变量
	int inum;
	pcap_if_t* alldevs;//所有网络适配器
	pcap_if_t* d;//选中的网络适配器
	char errbuf[PCAP_ERRBUF_SIZE];//错误缓冲区,大小为256
	char source[PCAP_ERRBUF_SIZE];
	pcap_t* adhandle;//捕捉实例,是pcap_open返回的对象
	int i = 0;//适配器计数变量
	struct pcap_pkthdr* header;//接收到的数据包的头部
	const u_char* pkt_data;//接收到的数据包的内容
	int res;//表示是否接收到了数据包
	u_int netmask;//过滤时用的子网掩码
	char packet_filter[] = "ip and udp";//过滤帧类型 实验包含ip and udp & arp & icmp

	struct bpf_program fcode;//pcap_compile所调用的结构体
	ip_header* ih;//ip头部
	u_int ip_len;//ip地址有效长度
	u_short sport, dport;//主机字节序列

	//用回调方法捕获数据包
	void packet_handler(u_char * param, const struct pcap_pkthdr* header, const u_char * pkt_data);
	//packet_handler指向一个可以接收数据包的函数。 这个函数会在收到每个新的数据包并收到一个通用状态时被libpcap所调用。

	//获得设备列表
	if (pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1) {
		fprintf(stderr, "Error in pcap_findalldevs: %s\n",
			errbuf);
		exit(1);
	}
	//打印设备列表
	for (d = alldevs; d; d = d->next) {
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	//选择设备
	if (i == 0) {
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}
	printf("Enter the interface number (1-%d):", i);
	scanf_s("%d", &inum);
	if (inum < 1 || inum > i) {
		printf("\nInterface number out of range.\n");
		//释放设备列表
		pcap_freealldevs(alldevs);
		return -1;
	}
	//选择到用户的设备
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);
	//打开设备
	if ((adhandle = pcap_open(d->name, 65536, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, errbuf)) == NULL) {
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n");//设备名，捕获包，混杂模式65536为所有包，混杂模式，时延，远程验证，错误缓冲
		pcap_freealldevs(alldevs);//释放设备列表，最后一步都要释放
		return -1;
	}

	//预处理
	if (pcap_datalink(adhandle) != DLT_EN10MB) {//检查链路层。只简单支持以太网。
		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
		pcap_freealldevs(alldevs);
		return -1;
	}
	if (d->addresses != NULL)
		netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.S_un.S_addr;//检索接口的第一个地址的掩码
	else
		netmask = 0xffffff;//如果接口没有地址，假设在一个C类网

	//编译和设置过滤器
	//编译过滤器
	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0) {
		fprintf(stderr, "\nUnable to compile the packet filter.Check the syntax.\n");
		pcap_freealldevs(alldevs);
		return -1;
	}
	//设置过滤器
	if (pcap_setfilter(adhandle, &fcode) < 0) {
		fprintf(stderr, "\nError setting the filter.\n");
		pcap_freealldevs(alldevs);
		return -1;
	}

	//开始捕获
	printf("\nlistening on %s...\n", d->description);
	pcap_freealldevs(alldevs);
	//开始捕获
	pcap_loop(adhandle, 0, packet_handler, NULL);//捕获数据包，捕获的数据包数，回调函数，回调函数的参数
}


void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)//通过libpcap的每一个传入的数据包调用回调函数
{
	struct tm* ltime;
	mac_header* mh;
	char timestr[16];
	ip_header* ih;
	time_t local_tv_sec;

	local_tv_sec = header->ts.tv_sec;//帧到达的时间
	ltime = localtime(&local_tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

	int length = sizeof(mac_header) + sizeof(ip_header);
	/*
	for (int i = 0; i < length; i++) {
		printf("%02X ", pkt_data[i]);//按二进制输出数据
		if ((i & 0xF) == 0xF)
			printf("\n");
	}
	printf("\n");
	*/

	//捕获后的处理
	mh = (mac_header*)pkt_data;
	ih = (ip_header*)(pkt_data + sizeof(mac_header)); //length of ethernet header；通过强制类型转换，将二进制数据值依次存入结构体中。

	//根据type储存第二位和第四位输出是什么类型的包
	if (mh->type[1] == 0 && mh->type[0] == 8)//ip为：0800  0001
	{
		printf("get an ip packet\n");
		if (ih->proto == 0x0001) {//进一步确定是icmp
			printf("get an icmp packet\n");
		}
	}
	else if (mh->type[1] == 6 && mh->type[0] == 8)//arp为0806
		printf("get an arp packet\n");

	printf("mac_header:\n");
	printf("\tdest_addr: ");
	for (int i = 0; i < 6; i++) {//输出mac地址
		if (i != 5)
			printf("%02x:", mh->dest_addr[i]);
		else
			printf("%02x\n", mh->dest_addr[i]);
	}
	printf("\tsrc_addr: ");
	for (int i = 0; i < 6; i++) {
		if (i != 5)
			printf("%02x:", mh->src_addr[i]);
		else
			printf("%02x\n", mh->src_addr[i]);
	}
	printf("\ttype: %04X", ntohs((u_short)mh->type));
	printf("\n");

	printf("ip_header\n");
	printf("\t%-10s: %02X\n", "ver_ihl", ih->ver_ihl);
	printf("\t%-10s: %02X\n", "tos", ih->tos);
	printf("\t%-10s: %04X\n", "tlen", ntohs(ih->tlen));//网络端序转为主机端序ntohs
	printf("\t%-10s: %04X\n", "identification", ntohs(ih->identification));
	printf("\t%-10s: %04X\n", "flags_fo", ntohs(ih->flags_fo));
	printf("\t%-10s: %02X\n", "ttl", ih->ttl);
	printf("\t%-10s: %02X\n", "proto", ih->proto);
	printf("\t%-10s: %04X\n", "crc", ntohs(ih->crc));
	printf("\t%-10s: %08X\n", "op_pad", ntohs(ih->op_pad));
	printf("\t%-10s: ", "saddr:");//输出ip地址
	for (int i = 0; i < 4; i++) {
		if (i != 3)
			printf("%d.", ih->saddr[i]);
		else
			printf("%d\n", ih->saddr[i]);
	}
	printf("\t%-10s: ", "daddr");
	for (int i = 0; i < 4; i++) {
		if (i != 3)
			printf("%d.", ih->daddr[i]);
		else
			printf("%d\n", ih->daddr[i]);
	}
	printf("\n");

	// 写文件
	FILE* fp = fopen("data.csv", "a+");//生成csv文件
	fprintf(fp, "get a packet\n");
	fprintf(fp, "time,%s\n", timestr);
	fprintf(fp, "src_mac,");
	for (int i = 0; i < 6; i++) {//写入mac源地址
		if (i != 5)
			fprintf(fp, "%02x:", mh->src_addr[i]);
		else
			fprintf(fp, "%02x\n", mh->src_addr[i]);
	}
	fprintf(fp, "dest_mac,");
	for (int i = 0; i < 6; i++) {//写入mac目的地址
		if (i != 5)
			fprintf(fp, "%02x:", mh->dest_addr[i]);
		else
			fprintf(fp, "%02x\n", mh->dest_addr[i]);
	}
	fprintf(fp, "src_ip,");
	for (int i = 0; i < 4; i++) {//写入ip源地址
		if (i != 3)
			fprintf(fp, "%02x:", ih->saddr[i]);
		else
			fprintf(fp, "%02x\n", ih->saddr[i]);
	}
	fprintf(fp, "dest_ip,");
	for (int i = 0; i < 4; i++) {//写入ip目的地址
		if (i != 3)
			fprintf(fp, "%02x:", ih->daddr[i]);
		else
			fprintf(fp, "%02x\n", ih->daddr[i]);
	}
	fprintf(fp, "len,%d\n\n", header->len);//输出帧长度

	fclose(fp);//关闭文件
}


