#include<iostream>
#define NO -1
using namespace std;
template<typename T>
class data {
		T *a;
		int n;
	public:
		data(T *t,int s):a(t),n(s) {}
		T sum() {
			T m=0;
			for(int i=0; i<n; i++)
				m+=a[i];
			return m;
		}
		int find(T s) {
			for(int i=0; i<n; i++)
				if(a[i]==s)
					return i;
			return NO;
		}
		void display() {
			for(int i=0; i<n; i++)
				cout<<a[i]<<" ";
		}
};
int main() {
	int a[]= {1,2,3,4,5,6,7,8,9};
	double b[]= {1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9};
	int c;
	double d;
	data<int> m(a,9);
	data<double> n(b,9);
	cout<<"数组m中的所有元素为：";
	m.display();
	cout<<endl;
	cout<<"数组n中的所有元素为：";
	n.display();
	cout<<endl;
	cout<<"数组m中的所有元素的和为：";
	cout<<m.sum()<<endl;
	cout<<"数组n中的所有元素的和为：";
	cout<<n.sum()<<endl;
	cout<<"查找数组m中的元素：";
	cin>>c;
	cout<<"元素所在位置为："<<m.find(c)<<endl;
	cout<<"查找数组n中的元素：";
	cin>>d;
	cout<<"元素所在位置为："<<n.find(d)<<endl;
}
