#include <bits/stdc++.h>
using namespace std;
class wdf{
	private:
		int a;
	public:
		wdf(int input):a(input){}
		void go(){
			cout << a;
		}
	private:
		int b;
}; 
int main(){
	int i;
	cin >> i;
	wdf num(i);
	cout << num.a; 
	num.go();
	return 0;
}
