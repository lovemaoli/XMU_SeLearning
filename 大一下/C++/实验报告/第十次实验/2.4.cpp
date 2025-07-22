#include <iostream>
class Animal;
void setValue(Animal&,int);
void setValue(Animal&,int,int);
class Animal {
	public:
		friend void Setvalue(Animal &,int);
		friend void Setvalue(Animal &,int,int);
	protected:
		int itsWeight;
		int itsAge;
};
void Setvalue(Animal& ta,int tw) {
	ta.itsWeight=tw;
}
void SetValue(Animal& ta,int tw,int tn) {
	ta.itsWeight=tw;
	ta.itsAge=tn;
}
int main() {
	Animal peppy;
	SetValue(peppy,5);
	SetValue(peppy,7,9);
	         return 0;
}

