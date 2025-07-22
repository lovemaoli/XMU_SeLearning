#include <iostream>
using namespace std;

class Parent {
	private:
		int m_nPrt;
	protected:
		int m_nPtd;
	public:
		int m_nPub;

	public:
		Parent(int var=-1) {
			m_nPub=var;
			m_nPtd=var;
			m_nPrt=var;
		}
};

class Child1: public Parent {
	public:
		int getPub() {
			return m_nPub;
		}
		int getPtd() {
			return m_nPtd;
		}

};

class Child2: protected Parent {
	public:
		int getPub() {
			return m_nPub;
		}
		int getPtd() {
			return m_nPtd;
		}
};

class Child3: private Parent {
	public:
		int getPub() {
			return m_nPub;
		}
		int getPtd() {
			return m_nPtd;
		}
};

int main() {
	Child1 cd1;
	Child2 cd2;
	Child3 cd3;

	int nVar=0;

	cd1.m_nPub=nVar;  //D
//	cd1.m_nPtd=nVar;   //E
	nVar=cd1.getPtd();   //F

//	cd2.m_nPub=nVar;  //G
	nVar=cd2.getPtd();   //H

//	cd3.m_nPub=nVar;  //I
	nVar=cd3.getPtd();   //J

	return 0;
}

