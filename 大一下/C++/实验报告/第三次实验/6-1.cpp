#include <iostream>
#include <string>
using namespace std;

int Myadd(int a,int b) {
    return (a + b);
}
double Myadd(double a, double b) {
    return (a + b);
}
string Myadd(string a, string b) {
    return (a + b);
}

int main()
{
    int a, b;
    double c, d;
    string s1, s2;

    cin >> a >> b;
    cin >> c >> d;
    cin >> s1 >> s2;

    cout << Myadd(a, b) << endl;
    cout << Myadd(c, d) << endl;
    cout << Myadd(s1, s2) << endl;

    return 0;
}

