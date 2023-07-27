#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
vector <string> s;
int main() {
	for(int i=1;i<=5;i++){
		string w;
		getline(cin,w);
		s.push_back(w);
	}
	sort(s.begin(),s.end());
	cout << "------- ÅÅÐò½á¹û ----------\n"; 
	for(auto i : s){
		cout << i << endl; 
	}
}

