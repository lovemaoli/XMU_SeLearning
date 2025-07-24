#include <iostream>
#include <cmath>
using namespace std;
#define MAX 100

class INT{

	int array[MAX];
	int length;

public:
	INT() {
		memset(array, '\0', MAX);
		array[0] = 1;//数组第一位用于表示符号
		length = 0;
	}

	~INT()	{
		delete[]array;
		length = 0;
	}

	INT(char* s){
		int len;
		len = strlen(s);
		if (s[0] == '-')
		{
			for (int i = 1; i < len; i++)
				array[i] = s[i] - '0';

			length = len-1;
		}//符号为负

		else
		{
			for (int i = 1; i <= len; i++)
				array[i] = s[i-1] - '0';
			array[0] = 1;	//第一个元素表示符号为正

			length = len;
		}//符号为正
	}//使用字符串s对INT进行初始化

	INT(const INT& ni) {
		memset(array, '\0', MAX);
		length = ni.length;
		for (int i = 0; i < length; i++)
			array[i] = ni.array[i];
	}

	INT(int i) {
		memset(array, '\0', MAX);
		length = 0;
		if (i < 0)array[0] = -1;
		else array[0] = 1;

		i = abs(i);
		for(int j=1;i;j++,i/=10)
		{
			length += 1;
			array[j] = i % 10;
		}//将int转化为数组元素

	}

	void show();
	INT operator+( INT& i);
	INT operator-( INT& i);
	INT operator*( INT& i);
	INT operator/( INT& i);
	INT operator=( INT& i);
	INT operator+(int i);
	INT operator-(int i);
	INT operator*(int i);
	INT operator/(int i);
	INT operator=(int i);
};

void INT::show() {
	if (array[0] == -1)
		cout << "-";	//第一个数组元素表示符号
	for (int j = 1; j < length; j++)
		cout << array[j];	//循环输出每个元素
}

INT INT::operator+( INT& i){
	INT ni;	//用ni保存结果,使用对象i对其初始化

	int j, k, l;//用于for循环计数
	if (length < i.length)ni.length = i.length;
	else ni.length = length;
	//不用考虑最大位数进位问题，直接让最大位数是两位数，不会影响最终输出
	if (array[0] == i.array[0])
	{
		for (j = length, k = i.length, l = ni.length; j >= 1&&k >= 1; l--, j--, k--)
		{
			array[l] = array[j] + i.array[k];
			if ((l - 1) != 0)
			{
				array[l - 1] += 1;
				array[l] -= 10;
			}//如果操作位数不是最大位数，进位,如果已经是最高位，不进位，直接存储2位数
		}//用数组实现大整数加法
		return ni;
	}
	else if (array[0] == -1 && i.array[0] == 1)
		return *this - i;
	else
		return i - *this;
}

