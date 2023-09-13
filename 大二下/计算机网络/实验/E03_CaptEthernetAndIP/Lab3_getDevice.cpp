#define HAVE_REMOTE //使PCAP_SRC_IF_STRING, NULL可被识别
#define WIN32 //防止引用unix库
#include "pcap.h"

int main()
{
    pcap_if_t* alldevs; //设备列表
    pcap_if_t* d;

    int i = 0;
    char errbuf[PCAP_ERRBUF_SIZE]; //错误信息

    /* 获取本地机器设备列表 */
    if (pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)//强制类型转化，将const char*类型转化为char*类型
    {
        fprintf(stderr, "Error in pcap_findalldevs_ex: %s\n", errbuf);
        return 1;
    }

    /* 打印列表 */
    for (d = alldevs; d != NULL; d = d->next)
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
        return 0;
    }

    // 释放设备列表
    pcap_freealldevs(alldevs);
}