#include <iostream>
using namespace std;

template<class T>
T my_min(T a, T b) {
	return((a < b) ? a : b);
}

int main() {
	int x = 1;
	int y = 2;
	cout << my_min(x, y) << endl;

	double x_d=0, y_d=1;
	cout << my_min(x_d, y_d) << endl;

	return 0;
}