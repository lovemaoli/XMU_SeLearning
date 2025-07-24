#include <iostream>
#include <string>
using namespace std;
template <class T>
void maxmin(T* x, int n, T* max, T* min) { //函数模板
	T tempmax = x[0];
	T tempmin = x[0];
	for (int i = 1; i < n; i++) {
		if (x[i] > tempmax)tempmax = x[i];
		if (x[i] < tempmin)tempmin = x[i];
	}
	*max = tempmax;
	*min = tempmin;
}

void maxmin(char** x, int n, char** max, char** min) { //同名显式函数
	char* tempmax = x[0];
	char* tempmin = x[0];
	for (int i = 1; i < n; i++) {
		if (strcmp(x[i], tempmax) > 0) tempmax = x[i];
		if (strcmp(x[i], tempmin) < 0)tempmin = x[i];
	}
	*max = tempmax;
	*min = tempmin;
}
int main() {
	int intArray[] = { 1, 2, 3, -4, 5, 6, 49 };
	int intMax, intMin;
	maxmin(intArray, 7, &intMax, &intMin);
	cout <<"最大值： "<< intMax << "  最小值： " << intMin << endl;

	double doubleArray[] = { 1.1, 2.2, 3.3, -4.4, 5.5, 6.6, 0.0 };
	double doubleMax, doubleMin;
	maxmin(doubleArray, 7, &doubleMax, &doubleMin);
	cout << "最大值： "<<doubleMax << "  最小值： " << doubleMin << endl;

	char* strArray[]= {"today","is","a","happy","day"};
	char* strMax, *strMin;
	maxmin(strArray, 5, &strMax, &strMin);
	cout << "最大值： "<<strMax << "  最小值： " << strMin << endl;

	return 0;
}
