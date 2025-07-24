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

const int max_license = 5;
std::map<std::string, int> license;
const int PORT = 8888;
string time_now()
{
    std::time_t now = std::time(nullptr);

    // 将时间戳转换为本地时间
    std::tm* localTime = std::localtime(&now);

    // 格式化时间字符串
    char timeStr[80];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
    return (string) timeStr;
}
// 处理客户端请求的线程函数
void clientThread(SOCKET clientSocket) 
{

    // 获取客户端地址信息
    sockaddr_in clientAddr;
    int addrLen = sizeof(clientAddr);
    getpeername(clientSocket, (struct sockaddr*)&clientAddr, &addrLen);

    // 将客户端地址转换为字符串形式
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr.sin_addr), ip, INET_ADDRSTRLEN);
    char buffer[1024] = { 0 };
    int bytesRead = recv(clientSocket, buffer, 1024, 0);

    if (bytesRead < 0)
    {
        std::cerr << time_now()<<"接收来自"<<ip<<"的消息失败" << std::endl;
        return;
    }
    string str = buffer;
    if (license.find(str) == license.end()|| license[str] < max_license)
    {
        string res = "ACCEPT";
        send(clientSocket, res.c_str(), res.size() + 1, 0);
        license[str]++;
        std::cout << time_now() << " 客户接入,"<<" 许可证为" << str << "，IP地址为 " << ip <<"，该许可证的用户数量为"<<license[str] << std::endl;
        while (true)
        {
            bytesRead = recv(clientSocket, buffer, 1024, 0);
            if (bytesRead > 0)
            {
                cout << time_now() << " 接收到许可证为" << str << ",ip地址为" << ip << "的用户状态报送" << endl;
            }
            else
            {
                cout << time_now() << " 许可证为" << str << ",ip地址为" << ip << "的用户已退出" << endl;
                license[str] --;
                return;
            }
        }
    }
    else
    {
        string res = "REJECT";
        std::cout << time_now() << " 客户接入," << " 许可证为" << str << "，IP地址为 " << ip << "，但该许可证的用户数量已满，客户接入失败" << std::endl;
        send(clientSocket, res.c_str(), res.size() + 1, 0);     
    }
    // 关闭客户端连接
    closesocket(clientSocket);
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
        // 创建线程处理客户端请求
        std::thread clientThreadOBJ(clientThread, clientSocket);
        clientThreadOBJ.detach(); // 分离线程，使其在完成任务后自动释放资源
    }

    // 关闭服务器套接字
    closesocket(serverSocket);

    // 清理 Winsock
    WSACleanup();

    return 0;
}