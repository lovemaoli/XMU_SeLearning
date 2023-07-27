#include <iostream>
using namespace std;
class Myclass
{
	public:
		Myclass(int g=4):gpa(g)
		{
			cout<<"ohh!!! a exactly student.\n";
			semeshours=100;
		}
	protected:
		int semeshours;
		float gpa;
};
int main()
{
	Myclass a[3],*p[2]; 
}
