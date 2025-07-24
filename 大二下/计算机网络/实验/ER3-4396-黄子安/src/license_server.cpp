#include <iostream>
#include <cstdio>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <map>
#include <chrono>
#include <string>
#include <thread>
using namespace std;
#pragma comment(lib,"Ws2_32.lib")

string get_license(char account[],char password[],char type[])
{
    //todo:将信息存入数据库
    //todo:从许可证池中获取一个许可证，这里用随机数代替
    int license = rand() + 1000000000;
    return to_string(license);
}
const int PORT = 6666;

string time_now()
{
    std::time_t now = std::time(nullptr);

    // 将时间戳转换为本地时间
    std::tm* localTime = std::localtime(&now);

    // 格式化时间字符串
    char timeStr[80];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
    return (string)timeStr;
}


int main()
{
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    int clientAddressLength = sizeof(clientAddress);

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "初始化 Winsock 失败" << std::endl;
        return -1;
    }

    // 创建套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cerr << "创建套接字失败" << std::endl;
        return -1;
    }

    // 设置服务器地址和端口
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // 绑定套接字到服务器地址和端口
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cerr << "绑定套接字失败" << std::endl;
        return -1;
    }

    // 监听连接
    if (listen(serverSocket, 5) == SOCKET_ERROR)
    {
        std::cerr << "监听失败" << std::endl;
        return -1;
    }

    std::cout << "等待客户端连接..." << std::endl;

    while (true)
    {
        // 接受客户端连接
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "接受连接失败" << std::endl;
            continue;
        }
        char account[80], password[80], type[80];
        if (recv(clientSocket, account, 1024, 0) < 0)
        {
            cerr << "接受数据失败" << endl;
        }

        if (recv(clientSocket, password, 1024, 0) < 0)
        {
            cerr << "接受数据失败" << endl;
        }

        if (recv(clientSocket, type, 1024, 0) < 0)
        {
            cerr << "接受数据失败" << endl;
        }

        string license=get_license(account,password,type);
        cout << time_now() << " 用户：" << account << "接入，并分配许可证" << license << endl;
        send(clientSocket, license.c_str(), license.size() + 1, 0);
    }

    closesocket(clientSocket);

    // 关闭服务器套接字
    closesocket(serverSocket);

    // 清理 Winsock
    WSACleanup();

    return 0;
}