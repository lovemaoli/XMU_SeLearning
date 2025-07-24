#include <iostream>
#include <cstring>
#include <cmath>
#define MAX(a,b) (a>b?a:b)
#define ABS(a) (a>=0?a:-a)
#define SWAP(x,y) ((x)=(x)+(y),(y)=(x)-(y),(x)=(x)-(y))
using namespace std;


int main() {
	int a,b;
	cin >> a >> b;
	SWAP(a,b);
	cout << MAX(a,b) << " " << ABS(b) << " " << a << " " << b << endl;
	return 0;
}


