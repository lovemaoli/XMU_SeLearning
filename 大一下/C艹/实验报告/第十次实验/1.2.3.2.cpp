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
		void print() const {
			cout<<"2:n="<<n<<endl;
		}
};
int main() {
	const Sample a(10);
	Sample b(20);
	a.print();
	b.print();
}

