#include <iostream>
#include <cstring>
#include <WS2tcpip.h>
#include <winsock2.h>
#include <Windows.h>
#include <time.h>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

const int PORT = 8888;
const char* SERVER_IP = "127.0.0.1";

const int REPORT_INTERVAL = 30 * 60;  // 状态报告间隔时间，单位为秒（30分钟）

bool stopFlag = false;  // 线程停止标志

void SendStatusReport(SOCKET clientSocket)
{
    while (!stopFlag)
    {
        // 发送状态报告到服务器
        string report = "status report";
        if (send(clientSocket, report.c_str(), report.size() + 1, 0) < 0) 
        {
            cerr << "发送状态报告失败" << std::endl;
        }
        this_thread::sleep_for(chrono::seconds(1800));       
    }
}
void softwareA()
{
    cout << "使用软件A中，按任意键结束软件A使用" << endl;
    getchar();
    getchar();
}
string get_license(const char account[],const char password[],const char type[])
{
    WSADATA wsaData;
    SOCKET clientSocket2;
    struct sockaddr_in serverAddress2;
    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
    {
        std::cerr << "初始化 Winsock 失败" << std::endl;
        exit(-1);
    }
    // 创建套接字
    clientSocket2 = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket2 == INVALID_SOCKET) {
        std::cerr << "创建套接字失败" << std::endl;
        exit(-1);
    }

    // 设置服务器地址和端口
    serverAddress2.sin_family = AF_INET;
    serverAddress2.sin_port = htons(6666);
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress2.sin_addr)) <= 0) {
        std::cerr << "无效的服务器地址" << std::endl;
        exit(-1);
    }

    // 连接服务器
    if (connect(clientSocket2, (struct sockaddr*)&serverAddress2, sizeof(serverAddress2)) < 0) {
        std::cerr << "连接服务器失败" << std::endl;
        exit(-1);
    }

    if (send(clientSocket2, account,strlen(account) + 1, 0) < 0) {
        std::cerr << "发送消息失败" << std::endl;
        exit(-1);
    }
    Sleep(1);
    if (send(clientSocket2, password, strlen(password) + 1, 0) < 0) {
        std::cerr << "发送消息失败" << std::endl;
        exit(-1);
    }
    Sleep(1);
    if (send(clientSocket2, type, strlen(type) + 1, 0) < 0) {
        std::cerr << "发送消息失败" << std::endl;
        exit(-1);
    }
    char buffer[1024] = { 0 };
    if (recv(clientSocket2, buffer, 1024, 0) < 0) {
        std::cerr << "接收响应失败" << std::endl;
        exit(-1);
    }
    // 关闭套接字

    closesocket(clientSocket2);

    // 清理 Winsock
    WSACleanup();
    return (string)buffer;
}
int main() 
{
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddress;
    cout << "已经拥有许可证？[Y/n]:";
    char c = getchar();
    if (c == 'N' || c == 'n')
    {
        string account, password, type;
        cout << "请输入你的用户名：";
        cin >> account;
        cout << "请输入你的密码：";
        cin >> password;
        cout << "请输入你的用户类型：";
        cin >> type;
        cout << "您的许可证为:" << get_license(account.c_str(), password.c_str(), type.c_str())<<"请务必牢记" << endl << endl;
    }

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "初始化 Winsock 失败" << std::endl;
        return -1;
    }

    // 创建套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "创建套接字失败" << std::endl;
        return -1;
    }

    // 设置服务器地址和端口
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "无效的服务器地址" << std::endl;
        return -1;
    }

    // 连接服务器
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "连接服务器失败" << std::endl;
        return -1;
    }

    // 发送数据到服务器
    string license;
    cout << "请输入10位许可证：";
    while (cin >> license && license.size() != 10) cout << " 许可证不合法，请重新输入：";
    if (send(clientSocket, license.c_str(), license.size() + 1, 0) < 0) {
        std::cerr << "发送消息失败" << std::endl;
        return -1;
    }

    // 接收服务器的响应
    char buffer[1024] = { 0 };
    if (recv(clientSocket, buffer, 1024, 0) < 0) {
        std::cerr << "接收响应失败" << std::endl;
        return -1;
    }
    string s = buffer;
    if (s == "ACCEPT")
    {
        cout << "允许使用" << endl;
        stopFlag = false;
        thread t(SendStatusReport, clientSocket);
        //使用软件A
        softwareA();
        stopFlag = true;
        t.detach();
    }
    else if (s == "REJECT")
    {
        cout << "当前许可证用户已满，请稍后再尝试";
        Sleep(10);
    }


    // 关闭套接字

    closesocket(clientSocket);

    // 清理 Winsock
    WSACleanup();

    return 0;
}
