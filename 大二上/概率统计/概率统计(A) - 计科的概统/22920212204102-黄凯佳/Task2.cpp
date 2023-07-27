#include <bits/stdc++.h>
using namespace std;

constexpr double D = 2;

int main() {
    ios::sync_with_stdio(false);
    vector<double> u(10001), r(10001);
    ifstream fin("data\\u2.dat");
    fin.tie(nullptr);
    for (int i = 1; i <= 10000; i++)
        fin >> u[i];
    for (int i = 1; i <= 10000; i++)
        r[i] = sqrt(-2 * D * log(u[i]));
    ofstream fout("data\\r2_2.dat");
    fout.tie(nullptr);
    for (int i = 1; i <= 10000; i++)
        fout << r[i] << " ";
    return 0;
}
