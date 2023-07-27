#include <iostream>
using namespace std;
template <class T>
class Sample {
		T n;
	public:
		Sample( )  {   }
		Sample(T i) {
			n=i;
		}
		Sample <T> & operator+ (const Sample<T> &);
		void disp( ) {
			cout<<"n="<<n<<endl;
		}
};
template <class T>
Sample<T> &Sample<T>::operator+(const Sample <T> & s)   {
	static Sample <T> temp;
	temp.n=n+s.n;
	return temp;
}
int main( ) {
	Sample <int> s1(10),s2(20),s3;
	s3=s1+s2;
	s3.disp( );
	return 0;
}

