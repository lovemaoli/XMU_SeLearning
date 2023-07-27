#include <iostream>
using namespace std;
class Base {
	public:
		Base(int a) : val(a) {   }
	private:
		int val;
};
class A {
	public:
		A(int v) : p(v),b(v) {  } //´íÎóĞŞ¸Ä´¦ 
		void print_val() {
			cout << "hello:" << p << endl;
		}
	private:
		int p;
		Base b;
};

int main() {
	int pp = 45;
	A b(pp);
	b.print_val();

	return 0;
}
