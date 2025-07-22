#include <iostream>
#include <iomanip>
int main()
{
	using namespace std;
	double a, b;
	cin >> a;
	cin >> b;
	cout << endl << setprecision(0) << a + b;
	cout << endl << setprecision(0) << a - b;
	cout << endl << setprecision(0) << a * b;
	cout << endl <<fixed << setprecision(2) << a / b;
	cout << endl;
}