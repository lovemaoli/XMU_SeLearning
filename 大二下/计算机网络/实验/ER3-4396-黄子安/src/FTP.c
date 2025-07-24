#define WIN32
#define _CRT_SECURE_NO_WARNINGS
#define ETHER_ADDR_LEN 6
#include <stdio.h>
#include <pcap.h>
#pragma comment(lib, "wpcap.lib")
FILE* fp;
typedef struct ip_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

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

typedef struct ether_header {
	u_char dist_mac[ETHER_ADDR_LEN];  //dist_MAC
	u_char src_mac[ETHER_ADDR_LEN];   //src_MAC
	u_short ether_type;               //ether_type
}ether_header;

typedef struct tcp_header
{
	u_short sport;
	u_short dsport;
	u_int seq;
	u_int ack_num;
	u_char ihl; 
	u_char frame;
	u_short wsize;
	u_short crc; 
	u_short urg;
}tcp_header;


void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	static char username[128], password[128];
	static is_successful=-1;
	struct tm* ltime;
	char timestr[40];
	char* payload;
	ip_header* ih;
	ether_header* eh;
	tcp_header* tcp;
	u_int ip_len;
	time_t local_tv_sec;

	/* retireve the position of the ether header */
	eh = (ether_header*)pkt_data;

	/* retireve the position of the ip header */
	ih = (ip_header*)(pkt_data + sizeof(ether_header)); //length of ethernet header

	tcp = (tcp_header*)(pkt_data + sizeof(ether_header) + sizeof(ip_header));


	/*get the payload to find User and Pass */
	payload = (u_char)(pkt_data + sizeof(ether_header)
		+ sizeof(ip_header) + sizeof(tcp_header));

	static int find_username = 0, find_password = 0;
	char* user = strstr(payload, "USER ");
	if (user != NULL)
	{
		char* end = strstr(user, "\r\n");
		if (end != NULL)
		{
			user += 5;
			int len = end - user;
			strncpy(username, user, len);
			username[len] = '\0';
			find_username = 1;		
		}
	}

	char* pass = strstr(payload, "PASS ");
	if (pass!=NULL)
	{
		pass += 5;
		char* end = strstr(pass, "\r\n");
		if (end != NULL)
		{
			int len = end - pass;
			strncpy(password, pass, len);
			password[len] = '\0';
			find_password = 1;
		}
	}

	char* succeed = strstr(payload, "230");
	if (succeed != NULL)
	{
		is_successful = 1;
	}

	char* failed = strstr(payload, "530");
	if (failed != NULL)
	{
		is_successful = 0;
	}

	if (find_username && find_password&&is_successful!=-1)
	{
		/* convert the timestamp to readable format */
		local_tv_sec = header->ts.tv_sec;
		ltime = localtime(&local_tv_sec);
		strftime(timestr, sizeof timestr, "%Y-%m-%d %H:%M:%S", ltime);

		printf("%s,", timestr);
		fprintf(fp, "%s,", timestr);

		printf("%02x:%02x:%02x:%02x:%02x:%02x,",
			eh->src_mac[0], eh->src_mac[1], eh->src_mac[2],
			eh->src_mac[3], eh->src_mac[4], eh->src_mac[5]);

		fprintf(fp, "%02x:%02x:%02x:%02x:%02x:%02x,",
			eh->src_mac[0], eh->src_mac[1], eh->src_mac[2],
			eh->src_mac[3], eh->src_mac[4], eh->src_mac[5]);


		printf("%d.%d.%d.%d,",
			ih->saddr.byte1,
			ih->saddr.byte2,
			ih->saddr.byte3,
			ih->saddr.byte4);

		fprintf(fp, "%d.%d.%d.%d,",
			ih->saddr.byte1,
			ih->saddr.byte2,
			ih->saddr.byte3,
			ih->saddr.byte4);

		printf("%02x:%02x:%02x:%02x:%02x:%02x,",
			eh->dist_mac[0], eh->dist_mac[1], eh->dist_mac[2],
			eh->dist_mac[3], eh->dist_mac[4], eh->dist_mac[5]);

		fprintf(fp, "%02x:%02x:%02x:%02x:%02x:%02x,",
			eh->dist_mac[0], eh->dist_mac[1], eh->dist_mac[2],
			eh->dist_mac[3], eh->dist_mac[4], eh->dist_mac[5]);

		printf("%d.%d.%d.%d,",
			ih->daddr.byte1,
			ih->daddr.byte2,
			ih->daddr.byte3,
			ih->daddr.byte4);

		fprintf(fp, "%d.%d.%d.%d,",
			ih->daddr.byte1,
			ih->daddr.byte2,
			ih->daddr.byte3,
			ih->daddr.byte4);

		printf("%s,", username);
		printf("%s,", password);
		printf("%s\n", is_successful ? "SUCCEED":"FAILED");

		fprintf(fp,"%s,", username);
		fprintf(fp,"%s,", password);
		fprintf(fp,"%s\n", is_successful ? "SUCCEED" : "FAILED");

		find_username = 0;
		find_password = 0;
		is_successful = -1;
		memset(username, 0, sizeof(username));
		memset(password, 0, sizeof(password));
	}
}

int main()
{
	pcap_if_t* alldevs;
	pcap_if_t* d;
	int inum;
	int i = 0;
	pcap_t* adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask;
	char packet_filter[] = "port 21";
	struct bpf_program fcode;

	fp = fopen("FTP.csv", "w+");
	if (!fp) exit(0);
	fprintf(fp, "时间,源 MAC,源 IP,目标 MAC,目标 IP,登录名,口令,成功与否\n");
	/* Retrieve the device list */
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/* Print the list */
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
	for (d = alldevs, i = 0; i < inum - 1;d = d->next, i++);

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

	/* Check the link layer. We support only Ethernet for simplicity. */
	if (pcap_datalink(adhandle) != DLT_EN10MB)
	{
		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
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


	//compile the filter
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

	/* At this point, we don't need any more the device list. Free it */
	pcap_freealldevs(alldevs);

	/* start the capture */
	pcap_loop(adhandle, 0, packet_handler, NULL);
	fclose(fp);
	return 0;
}
