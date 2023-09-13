#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<winsock.h>
#include <string.h>
#include<time.h>
#include<iostream>
#define MAX_MSG_SIZE 1024
#define SERVER_PORT 49152
#define BACKLOG 5    
char recData[MAX_MSG_SIZE];
char sendData[MAX_MSG_SIZE];
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main(int argc, char* argv[])
{
    printf("Lab6 TCP-客户端 文件名: data.txt\n");
    WORD sockVersion = MAKEWORD(2, 2);
    //创建套接字，返回一个描述符，这个描述符是一个整数，是套接字在系统中的唯一标识符，后面的操作都要用到这个描述符。
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0)
    {
        getchar(); getchar();
        return 0;
    }//上面这几句必不可少，否则无法创建socket插口，即socket（）会报错。

    SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //客户端的插口
    if (sclient == INVALID_SOCKET)
    {
        printf("invalid socket!");
        getchar(); getchar();
        return 0;
    }
    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(SERVER_PORT);
    serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//ip保留字段，本机地址
    //这就是要准备好server端的信息，便于插口去连接。    
    printf("连接server端\n");
    if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
    printf("connect error !");
    closesocket(sclient);
    getchar(); getchar();
    return 0;
    }     


    //char file_name[1000];
    //memset(file_name, 0, 1000);
    //strncpy(file_name, buffer, strlen(buffer) > FILE_NAME_MAX_SIZE ? FILE_NAME_MAX_SIZE : strlen(buffer));
    FILE* fp;
    if ((fp = fopen("data.txt", "r"))== NULL)
    {
        printf("文件不存在！\n");
    }
    else
    {
        printf("文件打开成功！\n");
        //bzero(buffer, BUFFER_SIZE);
        memset(sendData, 0, MAX_MSG_SIZE);
        int file_block_length = 0;
        //循环将文件file_name(fp)中的内容读取到sendData中
        int i = 0;
        while ((file_block_length = fread(sendData, sizeof(char), MAX_MSG_SIZE, fp)) > 0)
        {
            //测试
            i++;
            if (i == 2) {
                closesocket(sclient);
                WSACleanup();//终止对套接字库的使用。
                getchar(); getchar();
                return 0;
            }
            printf("读取到的文件长度file_block_length = %d\n", file_block_length);

            // 发送sendData中的字符串到new_server_socket,实际上就是发送给服务器端  
            if (send(sclient, sendData, MAX_MSG_SIZE, 0) < 0)
            {
                printf("文件发送失败！\n");
                break;
            }
            //清空sendData缓存区
            memset(sendData, 0, MAX_MSG_SIZE);//bzero(buffer, sizeof(buffer));
            memset(recData, 0, MAX_MSG_SIZE);
            int ret = recv(sclient, recData, MAX_MSG_SIZE, 0);//返回的是收到的实际字节数
            if (ret > 0)
            {

                printf(recData);
                printf("\n");
            }
            else if (ret <= 0) {
                printf("服务器 127.0.0.1:49152 失去连接!\n");
                getchar(); getchar();
                exit(-1);
            }
        }
        fclose(fp);  			//关闭文件描述符fp
        printf("文件传输成功！\n");
    }

    int ret = recv(sclient, recData, MAX_MSG_SIZE, 0);//返回的是收到的实际字节数
    if (ret > 0)
    {
        
        printf(recData);
        printf("\n");
    }
    else if (ret <= 0) {
        printf("服务器 127.0.0.1:49152 失去连接!\n");
        getchar(); getchar();
        exit(-1);
    }

    closesocket(sclient);
    WSACleanup();//终止对套接字库的使用。
    getchar(); getchar();
    return 0;
}

