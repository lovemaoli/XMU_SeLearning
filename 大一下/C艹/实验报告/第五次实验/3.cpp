#include <string>
#include <iostream>
using namespace std;
int main() {
	string s="He123l4l5o";
	string neww;
	for (string::size_type index=0; index!=s.size(); ++index) { //£¨*£©
		char ch=s[index];
		if (ch>='0'&&ch<='9')
			neww+=ch;
	}
	cout << neww;
}

