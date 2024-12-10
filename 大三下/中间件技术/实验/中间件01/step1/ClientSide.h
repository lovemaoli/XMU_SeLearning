#include <iostream>
#include <ws2tcpip.h>
#include <winsock.h>
#include <thread>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define SERVER_IP "127.0.0.1" //本机地址
#define SERVER_PORT 1145 

/*
	22920212204392 黄勖
	运行命令：
	g++	ClientSide.cpp -o ClientSide -lwsock32 -lws2_32
*/


class USER{
public:
    USER();
    char username[100]; //用户名
	char password[100]; //账号
	char type[100];  //协议类型
	bool is_used;   //是否占用
    char license[11];   //协议号
    sockaddr_in ServerAddress;  //IPV4 服务端地址族、服务端IP地址、服务端端口号
};
USER::USER() {
	username[0] = '\0';
	password[0] = '\0';
	is_used = false;
	type[0] = '\0';
	license[0] = '\0';
	//服务端信息
	ServerAddress.sin_addr.s_addr = inet_addr(SERVER_IP); //定义IP
	ServerAddress.sin_port = SERVER_PORT; //定义端口号
	ServerAddress.sin_family = PF_INET; //使用协议类型为（TCP/IP – IPv4）
};


void initialization();
int run();


void initialization() {
	//初始化套接字库
	WORD w_ver = MAKEWORD(2, 2);//版本号
	WSADATA wsaData;
	int err;
	err = WSAStartup(w_ver, &wsaData);
	if (err != 0) {
        cout << "客户端初始化失败" << endl;
        WSACleanup();
    }
	//检测版本号
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wHighVersion) != 2) {
		WSACleanup();
		cout << "客户端初始化失败" << endl;
	}
	cout << "客户端初始化成功" << endl;
}

int run(){
    //定义长度变量
	USER A;
	int send_len = 0;
	int recv_len = 0;
	//定义发送缓冲区和接受缓冲区
	char send_buf[100];
	char recv_buf[100];
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	initialization();
	
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);//吸收socket流判断是否链接
	if (s_server <= 0) {
		cerr << "socket连接失败" << endl;
		return 1;
	}
	if (connect(s_server, (SOCKADDR*)&A.ServerAddress, sizeof(SOCKADDR)) == -1) {
		cout << "客户端连接失败!" << endl;
		WSACleanup();
	}
	else {
		cout << "客户端连接成功!" << endl;
		cout << "连接 IP:" << SERVER_IP << " Port:" << SERVER_PORT  << endl; //创建成功
	}


	//发送,接收数据
	while (1) {
		recv_len = recv(s_server, recv_buf, 100, 0);
		if (recv_len < 0) {
			cout << "连接已断开! 接受失败!" << endl;
			cout << "正在尝试重新连接..." << endl;
			break;
		}
		else {
			cout << "服务端链接请求:" << recv_buf << endl;
		}
		cin >> send_buf;
		send_len = send(s_server, send_buf, 100, 0);
		if (send_len < 0) {
			cout << "连接已断开! 发送未成功!" << endl;
			cout << "正在尝试重新连接..." << endl;
			break;
		}
	}
	//关闭套接字
	closesocket(s_server);
	//释放DLL资源
	WSACleanup();
}

