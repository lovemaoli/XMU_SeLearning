#include <iostream>
using namespace std;
char* delete_point(char* curr){
	int dq=0;
	for (int index=0; curr[index]!='\0'; ++index) {
		if(curr[index]!=','&&curr[index]!='.'){
			curr[dq]=curr[index];
			dq++;
		}
	}
	curr[dq]='\0';
	return curr;
}
int main() {
	char s[100];
	cin >> s;
	delete_point(s);
	cout << s;

}

