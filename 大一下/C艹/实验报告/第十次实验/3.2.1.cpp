#include <iostream>
using namespace std;
class Sample {
	private:
		int x;
		
	public:
		static int y;  //Óï¾ä1
		Sample(int a) {
			x=a;
			x++;
			y++;
		}
		void print() {
			cout<<"x="<<x<<",y="<<y<<endl;
		}
};
int Sample::y=10;
int main() {
	Sample s1(20);
	cout<<Sample::y;
	Sample s2(30);
	s1.print();
	s2.print();
}

