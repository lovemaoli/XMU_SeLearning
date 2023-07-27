#include <iostream>
using namespace std;
class Sample {
		int x;
	public:
		Sample() {
			cout << "Sample()::executed." << endl; 
		};
		Sample(int a) {
			x=a;
			cout << "Sample(int a)::executed." << endl; 
		}
		Sample(Sample &a) {
			x=a.x+1;
			cout << "Sample(Sample &a)::executed." << endl; 
		}
		void disp() {
			cout << "void disp()::executed." << endl; 
			cout<<"x="<<x<<endl;
		}
};
int main() {
	Sample s1(2),s2(s1);
	s2.disp();
}

