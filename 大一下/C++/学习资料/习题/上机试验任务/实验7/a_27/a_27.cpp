#include <iostream>
using namespace std;
#define SIZE 10

class IntArray
{
private:
	int* array;
public:
	IntArray(){
		array = nullptr;
	}

	~IntArray(){
		delete[]array;
	}

	IntArray(int* a) {
		array = new int[SIZE];
		if (sizeof(a) / 4 > SIZE)
		{
			cout << "index bound!";
			exit(-1);
		}//下标越界检查
		for (int i = 0; i < sizeof(a)/4; i++)
			array[i] = a[i];
	}//实现数组整体赋值

	int length(){
		int i;
		for (i = 0; i < SIZE; i++)
			if (array[i] == '\0')break;
		return i;
	}

};


