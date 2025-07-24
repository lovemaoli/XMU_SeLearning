#include <iostream>
#include <cstring>
using namespace std;
int main(int argc, char *argv[]) {
	// 为原始数组开辟内存
	int* p = new int[5];
	for(int i = 0; i < 5; i++) {
		p[i] = i;
		cout << p[i] <<" ";
	}
	// 开辟一段更大的内存
	int *pointer = new int[10];
	// 将原始内存的数据 拷贝到新的内存里
	memcpy(pointer, p, sizeof(int) * 5);
	// 释放原始指针p的空间
	delete p;
	// 将指针p指向新的内存
	p = pointer;
	// 添加新的元素到数组中，并输出结果
	for(int i = 5; i < 10; i++) {
		p[i] = i;
		cout << p[i] << " ";
	}
	return 0;
}
