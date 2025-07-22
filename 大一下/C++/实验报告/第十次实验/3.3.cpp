#include <iostream>
using namespace std;
class Budget {
	private:
		static int CorpBudget;
		
	public:
		int num;
		Budget(int a) {
			num=a;
		}
		void addBudget(int add) {
			CorpBudget+=add;
		}
		void showBudget() {
			cout << CorpBudget << endl;
		}
};
int Budget::CorpBudget=0;
int main() {
	Budget s1(1);
	Budget s2(2);
	s1.showBudget();
    s1.addBudget(300);
    s2.addBudget(500);
	s2.showBudget();
	return 0;
}

