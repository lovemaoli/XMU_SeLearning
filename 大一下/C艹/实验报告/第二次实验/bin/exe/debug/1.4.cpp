#include <iostream >
using namespace std;
int fun(char *s);
int main() {
	const char *p="hello";
	cout<<fun("Hello");
	return 0;
}
int fun(char *s) {
	*s='h';
	return *s;
}

