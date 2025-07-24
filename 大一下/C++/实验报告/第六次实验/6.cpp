#include <iostream>
using namespace std;
class A {
 public:
   A(int x1)  { x=x1; }   //构造函数，有木有？
   void disp( )  { cout<<"\n this="<<this<<"when x="<<this->x; }
 private:
   int x;
};
int main() {
  A a(1),b(2),c(3);  //对象初始化
  a.disp();
  b.disp();
  c.disp();
  return 0;
}

