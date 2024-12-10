#include "ClientSide.h"

/*
	22920212204392 黄勖
	运行命令：
	g++	ClientSide.cpp -o ClientSide -lwsock32 -lws2_32
*/


int main() {
	
	system("chcp 65001");
	while (1) {
		run();
		Sleep(1000);
	}

	return 0;
}