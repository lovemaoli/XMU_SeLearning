#include <iostream>
using namespace std;
class Sample {
	private:
		int x;
		static int y;
	public:
		Sample(int a) {
			x=a;
			y+=x;
		}
		static void print(Sample s) {
			cout<<"x="<<x<<",y="<<y<<endl;
		}
};
int Sample::y=10;
int main() {
	Sample s1(20);
	Sample s2(30);
	s1.print(s1);
	s2.print(s2);
}

