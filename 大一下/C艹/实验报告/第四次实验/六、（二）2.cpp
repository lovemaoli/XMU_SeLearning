#include <iostream>
#include <cstring> 
using namespace std;

int main(int argc, const char * argv[])
{
	int length1,length2;
	cout << "输入字符串1长度："; 
	cin >> length1;
	cout << "输入字符串2长度："; 
	cin >> length2;
	char *p= new char[length1+length2+5];
	char *q= new char[length2+5];
	cin >> p;
	cin >> q;
	strcat(p,q);
	cout << p; 
    return 0;
}
