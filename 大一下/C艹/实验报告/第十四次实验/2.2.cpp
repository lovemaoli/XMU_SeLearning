#include <iostream>
using namespace std;
template <class T>
class Myclass {
	private:
		T n;
	public:
		Myclass(T a);
		T getn ();
		void setn(T b);
};
template <class T>
Myclass<T>::Myclass(T a) {
	n=a;
}
template <class T>
T Myclass<T>::getn() {
	return n;
}
template <class T>
void Myclass<T>::setn(T b) {
	n=b;
}

int main() {
	Myclass <double> obj1(10);
	cout<<"n="<<obj1.getn()<<endl;
	obj1.setn(20);
	cout<<"n="<<obj1.getn()<<endl;
	Myclass <char> obj2('a');
	cout<<"n="<<obj2.getn()<<endl;
	obj2.setn('b');
	cout<<"n="<<obj2.getn()<<endl;
}

