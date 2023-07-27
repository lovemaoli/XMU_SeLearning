#include __(1)___
#include <iostream>
using namespace std;
struct Student {
	int no;
	char name[10];
	int scores[5];
} s1;
void main() {
//以二进制方式输入数据
	ifstream in_file("d:\\students.dat",__(2)__);
	if(_____(3)____) {
		cerr<<"Fail to open file"<<endl;
		exit(-1);
	}
	in_file.read(_____(4)____);
	in_file.close();
}
