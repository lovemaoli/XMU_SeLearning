#include <iostream>
#include <string>
#include "worker.h" 
using namespace std;

int main() {
	Teacher_Cadre person("ZhangLei", 23, 'M', "Beijing", 87891611, "professor", "assitant", 8981.4);
	person.show();
	system("pause");
	return 0; 
}
