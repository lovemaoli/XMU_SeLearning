#include <iostream>
using namespace std;
class MyBASE {
		int k;
	public:
		void set(int n) {
			k=n;
		}
	protected:
		int get() const {
			return k;
		}
};
class MyDERIVED: protected MyBASE {
		int j;
	public:
		void set(int m, int n) {
			MyBASE::set(m);
			j=n;
		}
		int get() const {
			return MyBASE::get()+j;
		}
};
int main() {

}
