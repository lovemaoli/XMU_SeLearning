#include <bits/stdc++.h>
using namespace std;
class Rectangle {
	private:
		int a,b,c;
	public:
		void calc() {
			cout << "长：" << a << "宽：" << b << "高：" << c << "体积：" << a*b*c << endl;
		}
		int setdata(int y,int m,int d) {
			if(y < 0 || m < 0 || d < 0) {
				cout << "num error" << endl;
				return -1;
			}
			a = y;
			b = m;
			c = d;
			return 0;
		}

};
int main() {
	Rectangle a1;
	cout << "plz input a,b,c:";
	int i,j,k;
	cin >> i >> j >> k;
	if(a1.setdata(i,j,k) == 0){
		a1.calc();
	}
	return 0;
}
