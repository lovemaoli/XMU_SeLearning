#include <iostream>
using namespace std;
class Sample {
		int n;
	public:
		Sample(int i) {
			n=i;
		};
		void print() {
			cout<<"1:n="<<n<<endl;
		}
};
int main() {
	const Sample a(10);
	a.print();
//error C2662: 'print'
//	cannot convert 'this' pointer
//	from 'const class Sample' to 'class Sample &'
//Conversion loses qualifiers
}

