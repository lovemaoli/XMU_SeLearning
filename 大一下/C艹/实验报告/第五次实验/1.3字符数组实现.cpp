#include <cstring>
#include <iostream>
using namespace std;
int main() {
	char str1[]="ABC";
	char str2[]="DEF";
	char str3[10]="";
	strcat(str3,str1);
	strcat(str3,str2);
	cout<<str3<<endl;
	strcat(str3,"GHI");
	cout<<str3<<endl;
}

