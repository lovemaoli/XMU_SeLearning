#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main() {
	string str; //C++输入流完全支持string类型，没必要定义C的字符buffer。
	cin>>str; //输入字符串
	reverse(str.begin(), str.end()); //str执行完这句，就已经是逆序结果。
	cout<<str<<endl;
	return 0; 
}
