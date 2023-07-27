#include <iostream>
using namespace std;
struct Complex {
	int shi;
	int xu;
};
void set_value(struct Complex &a,int s,int x) {
	a.shi=s;
	a.xu=x;
}
void display(struct Complex &a) {
	cout<<"实部为："<< a.shi << " 虚部为："<< a.xu << endl;
}
void addi1(struct Complex &a,struct Complex &b) {
	a.shi+=b.shi;
	a.xu+=b.xu;
}
struct Complex addi2(struct Complex &a,struct Complex &b) {
	struct Complex sum;
	sum.shi=a.shi+b.shi;
	sum.xu=a.xu+b.xu;
	return sum;
}
struct Complex & addi3(struct Complex &a,struct Complex &b) {
	struct Complex sum;
	sum.shi=a.shi+b.shi;
	sum.xu=a.xu+b.xu;
	return sum;
}

int main() {
	struct Complex a1,b1,c1;
	set_value(a1,1,2);
	set_value(b1,2,3);
	addi3(a1,b1) = a1;
	c1 = addi3(a1,b1);
	cout << &(addi2(a1,b1)) << endl; 
	display(c1);
	return 0;
}
