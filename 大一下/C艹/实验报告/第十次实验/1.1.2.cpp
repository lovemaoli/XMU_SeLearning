#include <iostream>
using namespace std;
class Init {
	private:
		const int num;
		int count;
	public:
		Init() :num(1){
			count=10;
		}
		void print() {
			cout<<num<<count<<endl;
		}
};
int main() {
	Init obj;
	obj.print();
}

