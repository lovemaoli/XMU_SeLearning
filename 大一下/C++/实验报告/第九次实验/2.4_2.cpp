#include <iostream>
using namespace std;
class Sample {
		int x;
	public:
		Sample() { };
		Sample(int a) {
			x=a;
		}
		Sample(Sample &a) {
			x=a.x+1;
		}
		void disp() {
			cout<<"x="<<x<<endl;
		}
};
int main() {
	Sample s1(2),s2(s1);
	s2.disp();
}

