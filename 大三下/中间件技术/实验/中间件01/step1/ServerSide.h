#include <iostream>
#include <ws2tcpip.h>
#include <winsock.h>
#include <thread>
#include <map>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 1145
#define USER_SIZE 50

/*
    22920212204392 黄勖
    运行命令：
    g++	ServerSide.cpp -o ServerSide -lwsock32 -lws2_32
*/

class USER {
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

static map<string, int> license_used_num;
USER users[USER_SIZE];
static int user_index = 1;
int user_choice = 0;

void initialization();
int search_user_type(USER user);
bool search_non_overload(char* A);
void iniaUSER();
int run();


//检验是否为新用户 2是新用户 1老用户密码正确 0老用户密码错误
int search_user_type(USER user) {
    for (int i = 1; i < user_index; i++) {
        if (strlen(users[i].username) == 0) continue;
        if (strcmp(user.username, users[i].username) == 0) {
            // cout << "==" << i << " " << users[i].username << endl;//cerr
            if (strcmp(user.password, users[i].password) == 0) {
                return 1;
            }
            return 0;
        }
    }
    return 2;
}

//查询许可证是否超过服务器限制
bool search_non_overload(char* A) {
    if (license_used_num[string(A)] > 9) {
        return false;
    }
    for (int i = 1; i < user_index; i++) {
        if (strlen(users[i].username) == 0) continue;
        if (strcmp(users[i].license, A) == 0) {
            license_used_num[string(A)] += 1;
            return true;
        }
    }
    return false;
}


void init_first_user() {
    strcpy(users[0].username, "user_0");
    strcpy(users[0].password, "user_0");
    users[0].type[0] = 'A';
    users[0].is_used = true;
    strcpy(users[0].license, "2002042800");
    license_used_num["2002042800"]++;
}


void initialization() {
    //初始化套接字库
    WORD w_req = MAKEWORD(2, 2);//版本号
    WSADATA wsadata;
    int err;
    err = WSAStartup(w_req, &wsadata);
    if (err != 0) {
        cout << "初始化socket失败!" << endl;
    }
    // else {
    //     cout << "初始化socket成功！" << endl;
    // }
    //检测版本号
    if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
        cout << "初始化socket失败!" << endl;
        WSACleanup();
    }
    else {
        cout << "初始化socket成功!" << endl;
    }
}
//填充服务端地址信息


int run() {

#pragma region 定义变量

    init_first_user();//初始化一个已经存在的用户的数据
    // cout << users[0].username;
    int send_len = 0;
    int recv_len = 0;
    int len = 0;
    //发送缓冲区和接受缓冲区
    char send_buf[100];
    char recv_buf[100];
    //服务端套接字，接受请求套接字
    SOCKET s_server;
    SOCKET s_accept;
    //服务端地址客户端地址
    SOCKADDR_IN server_addr;
    SOCKADDR_IN accept_addr;
    initialization();

#pragma endregion

#pragma region 初始化

    //创建套接字
    s_server = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(s_server, (SOCKADDR*)&users[0].ServerAddress, sizeof(SOCKADDR)) == -1) {
        cout << "套接字绑定失败!" << endl;
        WSACleanup();
    }

    //设置套接字为监听状态
    if (listen(s_server, SOMAXCONN) < 0) {
        cout << "设置监听状态失败!" << endl;
        WSACleanup();
    }

    cout << "正在监听" << endl;
    //接受连接请求
    len = sizeof(SOCKADDR);
    s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
    if (s_accept == SOCKET_ERROR) {
        cout << "连接失败!" << endl;
        WSACleanup();
        return -1;
    }
    cout << "成功建立链接，等待发信" << endl;
    //接收数据

#pragma endregion

#pragma region 用户选择
    //发信用户名
    strcpy(send_buf, "请输入 0: 登陆服务端 1: 暂未开放留作接口");
    send_len = send(s_accept, send_buf, 100, 0);
    if (send_len < 0) {
        cout << "Error: 用户选择请求提交错误！" << endl;
        return -1;
    }
    else {
        cout << "log: 已发送用户选择请求" << endl;
    }//发信：用户选择请求

    recv_len = recv(s_accept, recv_buf, 100, 0);
    //发信检查是否收到用户选择
    if (recv_len < 0) {
        cout << "Error: 接受用户选择信息失败!" << endl;
        return -1;
    }
    else {
        cout << "log: 已收到用户选择消息: " << recv_buf << endl;
    }//收信：接受用户选择请求
    if (recv_buf[0] == '0') user_choice = 0;
    else user_choice = 1;

    if (user_choice != 0) {
        cout << "请输入0" << endl;
        return -1;
    }

#pragma endregion

#pragma region 登陆服务端
    //
    //!!购买许可证, 需要输入用户名 密码 许可证类型
    //
    cout << "log: user_index: " << user_index << endl;//cerr
    //输入用户名
    if (user_choice == 0) {
        //发信检查是否成功发送
        strcpy(send_buf, "请输入用户名");
        send_len = send(s_accept, send_buf, 100, 0);
        if (send_len < 0) {
            cout << "Error: 用户名请求提交错误！" << endl; return -1;
            return -1;
        }
        else {
            cout << "log: 已发送用户名请求" << endl;
        }//发信：用户名请求
        recv_len = recv(s_accept, recv_buf, 100, 0);
        //发信检查是否收到用户名
        if (recv_len < 0) {
            cout << "Error: 接受用户信息失败！" << endl; return -1;
            return -1;
        }
        else {
            cout << "log: 已收到用户名消息:" << recv_buf << endl;
        }//收信：接受用户名
        strcpy(users[user_index].username, recv_buf);
    }

    //输入用户密码
    strcpy(send_buf, "请输入密码");
    //发信检查是否成功发送
    send_len = send(s_accept, send_buf, 100, 0);
    if (send_len < 0) {
        cout << "Error: 密码请求提交错误！" << endl; return -1;
    }
    else {
        cout << "log: 已发送密码请求" << endl;
    }//发信：密码请求
    recv_len = recv(s_accept, recv_buf, 100, 0);
    //发信检查是否收到密码
    if (recv_len < 0) {
        cout << "Error: 接受密码信息失败！" << endl; return -1;
    }
    else {
        cout << "log: 已收到密码消息:" << recv_buf << endl;
    }//收信：接受密码
    strcpy(users[user_index].password, recv_buf);


    //查你成分 判断是否新用户
    if (search_user_type(users[user_index]) == 2) {
        cout << "新用户注册成功" << endl;

        strcpy(send_buf, "是否选择关机?(Y代表是,N代表否)");
        send_len = send(s_accept, send_buf, 100, 0);
        if (send_len < 0) {
            cout << "Error: 关机请求提交错误！" << endl; return -1;
        }
        else {
            cout << "log: 已发送关机请求" << endl;
        }//发信：关机请求

        recv_len = recv(s_accept, recv_buf, 100, 0);
        //发信检查是否收到关机消息
        if (recv_len < 0) {
            cout << "Error: 接受关机信息失败！" << endl; return -1;
        }
        else {
            cout << "log: 已收到关机消息:" << recv_buf << endl;
        }//收信：接受关机消息

        if (strcmp(recv_buf, "Y") == 0) {
            cout << "已收到关机请求, 即将关机" << endl;
            strcpy(send_buf, "已收到关机请求, 即将关机");
            send_len = send(s_accept, send_buf, 100, 0);
            if (send_len < 0) {
                cout << "Error: 关机请求提交错误！" << endl; return -1;
            }
            else {
                cout << "log: 已发送关机请求" << endl;
            }//发信：关机请求
            // system ("shutdown -s -t 60");
        }
        else {
            cout << "已收到不关机请求, 那就不关机" << endl;
            strcpy(send_buf, "已收到不关机请求, 那就不关机");
            send_len = send(s_accept, send_buf, 100, 0);
            if (send_len < 0) {
                cout << "Error: 关机请求提交错误！" << endl; return -1;
            }
            else {
                cout << "log: 已发送关机请求" << endl;
            }//发信：关机请求
        }

    }

    //老用户
    else {
        //密码输不对是吧
        while (search_user_type(users[user_index]) == 0) {
            //输入用户密码
            strcpy(send_buf, "用户名正确, 密码错误! 再次输入密码: ");
            //发信检查是否成功发送
            send_len = send(s_accept, send_buf, 100, 0);
            if (send_len < 0) {
                cout << "Error: 密码请求提交错误！" << endl; return -1;
            }
            else {
                cout << "log: 已发送密码请求" << endl;
            }//发信：密码请求
            recv_len = recv(s_accept, recv_buf, 100, 0);
            //发信检查是否收到密码
            if (recv_len < 0) {
                cout << "Error: 接受密码信息失败！" << endl; return -1;
            }
            else {
                cout << "log: 已收到密码消息:" << recv_buf << endl;
            }//收信：接受密码
            strcpy(users[user_index].password, recv_buf);
        }

        strcpy(send_buf, "用户登陆成功");
        send_len = send(s_accept, send_buf, 100, 0);
        if (send_len < 0) {
            cout << "Error: 用户登陆成功消息提交失败!" << endl; return -1;
        }
        else {
            cout << "log: 已发送用户登陆成功消息" << endl;
        }//发信：用户登陆成功

        strcpy(send_buf, "是否选择关机?(Y代表是,N代表否)");
        send_len = send(s_accept, send_buf, 100, 0);
        if (send_len < 0) {
            cout << "Error: 关机请求提交错误！" << endl; return -1;
        }
        else {
            cout << "log: 已发送关机请求" << endl;
        }//发信：关机请求

        recv_len = recv(s_accept, recv_buf, 100, 0);
        //发信检查是否收到关机消息
        if (recv_len < 0) {
            cout << "Error: 接受关机信息失败！" << endl; return -1;
        }
        else {
            cout << "log: 已收到关机消息:" << recv_buf << endl;
        }//收信：接受关机消息


        if (strcmp(recv_buf, "Y") == 0) {
            cout << "已收到关机请求, 即将关机" << endl;
            strcpy(send_buf, "已收到关机请求, 即将关机");
            send_len = send(s_accept, send_buf, 100, 0);
            if (send_len < 0) {
                cout << "Error: 关机请求提交错误！" << endl; return -1;
            }
            else {
                cout << "log: 已发送关机请求" << endl;
            }//发信：关机请求
            // system ("shutdown -s -t 60");
        }
        else {
            cout << "已收到不关机请求, 那就不关机" << endl;
            strcpy(send_buf, "已收到不关机请求, 那就不关机");
            send_len = send(s_accept, send_buf, 100, 0);
            if (send_len < 0) {
                cout << "Error: 关机请求提交错误！" << endl; return -1;
            }
            else {
                cout << "log: 已发送关机请求" << endl;
            }//发信：关机请求
        }
    }

#pragma endregion

    user_index++;

    //关闭套接字
    closesocket(s_server);
    closesocket(s_accept);
    //释放DLL资源
    WSACleanup();
}
