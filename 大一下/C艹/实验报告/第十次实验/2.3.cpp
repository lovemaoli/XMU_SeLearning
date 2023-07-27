#include <iostream>
class Animal;
void setValue(Animal&,int);
void setValue(Animal&,int,int);
class Animal {
	public:
		//friend void Setvalue(Animal &,int);
		//friend void Setvalue(Animal &,int,int);
		int* getweight()const{
			return const_cast<int*>(&itsWeight);
		}
		int* getAge()const{
			return const_cast<int*>(&itsAge);
		}
	protected:
		int itsWeight;
		int itsAge;
};
void Setvalue(Animal& ta,int tw) {
	*ta.getweight()=tw;
}
void Setvalue(Animal& ta,int tw,int tn) {
	*ta.getweight()=tw;
	*ta.getAge()=tn;
}
int main() {
	Animal peppy;
	Setvalue(peppy,5);
	Setvalue(peppy,7,9);
	         return 0;
}

