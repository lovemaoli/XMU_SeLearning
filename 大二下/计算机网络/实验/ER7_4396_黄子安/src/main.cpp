#include <winsock2.h>
#include <iostream>
#include <thread>
#include <bitset>
#include <vector>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib") 
using namespace std;

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

void clientThread(SOCKET clientSocket)
{
    // 获取客户端地址信息
    sockaddr_in clientAddr;
    int addrLen = sizeof(clientAddr);
    getpeername(clientSocket, (struct sockaddr*)&clientAddr, &addrLen);

    // 将客户端地址转换为字符串形式
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr.sin_addr), ip, INET_ADDRSTRLEN);


    //接收到来自客户端的连接请求
    char buf[2048];
    int len = recv(clientSocket, buf, sizeof(buf), 0);

    uint32_t dst_ip = *(uint32_t*)(buf + 4);
    uint16_t dst_port = ntohs(*(uint16_t*)(buf + 2));
    struct in_addr inaddr;
    inaddr.s_addr = dst_ip;
    char* dst_ip_str = inet_ntoa(inaddr);
    cout<< time_now() <<" 客户端接入并访问：" << dst_ip_str << ":" << dst_port << endl;

    int targetSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (targetSocket < 0) {
        return;
    }
    struct sockaddr_in targetAddr;
    memset(&targetAddr, 0, sizeof(targetAddr));
    targetAddr.sin_family = AF_INET;
    targetAddr.sin_port = htons(dst_port);  
    targetAddr.sin_addr.s_addr = inet_addr(dst_ip_str);

    connect(targetSocket, (struct sockaddr*)&targetAddr, sizeof(targetAddr));

    char success_response[8] = { 0x00,0x5A };
    send(clientSocket, success_response, sizeof(success_response), 0);

    // 使用select函数实现IO多路复用
    fd_set readfds;
    int maxfd = max(clientSocket, targetSocket) + 1;
    vector<SOCKET> sockets;
    sockets.push_back(clientSocket);
    sockets.push_back(targetSocket);

    char buffer[4096];
    int bytes_read, bytes_written;

    while (true) {
        FD_ZERO(&readfds);
        for (auto s : sockets) {
            FD_SET(s, &readfds);
        }
        if (select(0, &readfds, NULL, NULL, NULL) == SOCKET_ERROR) {
            cerr << "select failed: " << WSAGetLastError() << endl;
            closesocket(clientSocket);
            closesocket(targetSocket);
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        for (auto s : sockets) {
            if (FD_ISSET(s, &readfds)) {
                bytes_read = recv(s, buffer, sizeof(buffer), 0);
                if (bytes_read <= 0) {
                    // 关闭socket并从sockets中删除
                    closesocket(s);
                    auto it = find(sockets.begin(), sockets.end(), s);
                    if (it != sockets.end()) {
                        sockets.erase(it);
                    }
                }
                else {
                    // 转发数据
                    int target = (s == clientSocket) ? targetSocket : clientSocket;
                    bytes_written = send(target, buffer, bytes_read, 0);
                    if (bytes_written <= 0) {
                        cerr << "send failed: " << WSAGetLastError() << endl;
                        closesocket(clientSocket);
                        closesocket(targetSocket);
                        WSACleanup();
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }

    // 关闭与目标服务器的连接
    closesocket(targetSocket);
    closesocket(clientSocket);
}
int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    int clientAddressLength = sizeof(clientAddress);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "初始化 Winsock 失败" << std::endl;
        return -1;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cerr << "创建套接字失败" << std::endl;
        return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("192.168.10.1");
    serverAddress.sin_port = htons(1800);

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
        if (clientSocket == INVALID_SOCKET)
        {
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
