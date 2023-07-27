#include <iostream>
#include <string>
#include <vector> 
using namespace std;
vector<string> save; 
void encrypt(string s){
	string cache;
	save.push_back(s);
	for(auto i : s){ //	相当于for(string::size_type i=0;s[i]!='\0';i++){
		cache.insert(cache.end(),i+8);
	} 
	cout << "加密内容：" << cache << endl;
}
void outcrypt(string s){
	string cache;
	for(auto i : s){ //	相当于for(string::size_type i=0;s[i]!='\0';i++){
		cache.insert(cache.end(),i-8);
	}
	for(auto i : save){
		if(i == cache){
			cout << "解密成功：" << cache << endl; 
			return;
		}
	}
	cout << "解密失败！" << endl;
}
int main() {
	while(1){
		cout<<"-----------------------\n";
		cout<<"-----字符加密系统------\n";
		cout<<"-----------------------\n";
		cout<<"--------[1]加密--------\n";
		cout<<"--------[2]解密--------\n";
		cout<<"------[Ctrl+C]退出-----\n";
		cout<<"-----------------------\n";
		int a;
		cin >> a;
		if(a==1){
			cout<<"请输入："<<endl;
			string w;
			getline(cin,w);
			getline(cin,w);
			encrypt(w);
		} 
		if(a==2){
			cout<<"请输入："<<endl;
			string w;
			getline(cin,w);
			getline(cin,w);
			outcrypt(w);
		} 
	}
	
}

