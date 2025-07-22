#include <cstring>
#include <iostream>
using namespace std;
int main() {
	char set1[10]="XYZ";
	char set2[10]="XYY";
	if(strcmp(set1,set2)>=1){
		cout << "set1更大"<<endl; 
	} 
	char set3[10]="XYZ";
	if(strcmp(set1,set3)==0){
		cout << "set1与set3相等"; 
	} 
	return 0;
}

