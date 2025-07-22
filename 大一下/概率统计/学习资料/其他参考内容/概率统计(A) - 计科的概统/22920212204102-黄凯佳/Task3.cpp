#include <bits/stdc++.h>
using namespace std;

constexpr double pi = acos(-1);

int main() {
    ios::sync_with_stdio(false);
    vector<double> u1(10001), u2(10001), X(10001);
    ifstream fin1("data\\u1.dat"), fin2("data\\u2.dat");
    fin1.tie(nullptr);
    fin2.tie(nullptr);
    for (int i = 1; i <= 10000; i++)
        fin1 >> u1[i];
    for (int i = 1; i <= 10000; i++)
        fin2 >> u2[i];
    for (int i = 1; i <= 10000; i++)
        X[i] = sqrt(-2 * 2 * log(u1[i])) * sin(2 * pi * u2[i]);
    ofstream fout("data\\Y_2.dat");
    fout.tie(nullptr);
    for (int i = 1; i <= 10000; i++)
        fout << X[i] << " ";
    return 0;
}
