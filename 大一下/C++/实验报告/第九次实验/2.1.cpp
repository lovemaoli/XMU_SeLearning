#include <iostream>
using namespace std;
class Base {
	public:
		Base(int a) : val(a) {  
			cout << "Base:: The function executes." << endl;
		}
	private:
		int val;
};
class A {
	public:
		A(int v) : p(v), b(v) { 
			cout << "A:: The function executes." << endl;
		}
		void print_val() {
			cout << "hello:" << p << endl;
		}
	private:
		int p;
		Base b;
};
int main() {
	int pp = 45;
	A b(pp),c(b);

	b.print_val();
	c.print_val();
	return 0;
}
