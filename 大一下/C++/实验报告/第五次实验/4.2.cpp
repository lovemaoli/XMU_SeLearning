#include <string>
#include <iostream>
using namespace std;
string delete_point(string& curr){
	for (string::size_type index=0; curr[index]!='\0'; ++index) {
		if(curr[index]==','||curr[index]=='.'){
			curr.erase(curr.begin()+index);
			index--;
		}
	}
	return curr;
}
int main() {
	string s;
	getline(cin,s);
	delete_point(s);
	cout << s;
	return 0; 
}

