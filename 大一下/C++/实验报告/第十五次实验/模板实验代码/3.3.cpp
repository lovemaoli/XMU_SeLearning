#include <iostream>
#define MAXSIZE 50
using namespace std;

template <class T>
class stack {
	private:
		T s[MAXSIZE];
		int top;
	public:
		stack() {
			top=-1;
		}
		void push(T newvalue); //进栈
		T pop( );  //出栈
};

template <class T>
void stack<T>::push(T newvalue) {
	if (top!=MAXSIZE) {
		top=top+1;
		s[top]=newvalue;
	} else
		cout<<"栈满，无法进栈！"<<endl;
}

template <class T>
T  stack<T>::pop() {
	if (top>-1) {
		cout<<s[top]<<endl;
		top=top-1;
	} else
		cout<<"堆栈已空!无法出栈！"<<endl;
}

int main( ) {
	stack<int> args;
	args.push(10);
	args.push(20);
	args.pop( );
	args.pop( );
	args.pop( );
}

