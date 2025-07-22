#include<iostream>
using namespace std;
class Rectangle {
	private:
		int length;
		int width;
	public:
		Rectangle() {};
		Rectangle(int a,int b):length(a),width(b) {};
		friend bool operator<(Rectangle&r,Rectangle&l) {
			if(r.length*r.width<l.length*l.width) {
				return 1;
			} else return 0;
		}
		friend bool operator<(Rectangle&r,int l) {
			if(r.length*r.width<l) {
				return 1;
			} else return 0;
		}
		friend bool operator<(int r,Rectangle&l) {
			if(r<l.length*l.width) {
				return 1;
			} else return 0;
		}
};


int main() {
	Rectangle p1(1,2),p2(2,3);
	cout<<(p1<p2)<<endl;
	cout<<(p1<3)<<endl;
	cout<<(3<p1)<<endl;
	cout<<(3<p1<p2)<<endl;
	return 0;
}
