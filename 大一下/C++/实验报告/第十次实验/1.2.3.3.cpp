#include <iostream>
using namespace std;
class Sample {
		int n;
	public:
		Sample(int i) {
			n=i;
		};
		void print() const;
		void setValue() {
			n=100;
		}
};
A

int main() {
	const Sample a(10);
	a.print();
}
void Sample::print() const {
	//n=200; //error C2166:I-value spectfies const object
	//setValue();//error C2662; 'setValue'cannot convert 'this' pointer
	//trom 'const class Sample' to 'class Sample &
	cout<< "2:n="<<n<<endl;
}
