#include <iostream>
using namespace std;
class Sample {
		int n;
	public:
		Sample(int i) {
			n=i;
		};
		void print() const;
};
int main() {
	const Sample a(10);
	a.print();
}
void Sample::print() const {
	cout << "2:n=" << n <<endl;
}

