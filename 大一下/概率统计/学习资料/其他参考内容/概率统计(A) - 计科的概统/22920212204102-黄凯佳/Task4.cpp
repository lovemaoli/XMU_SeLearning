#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    vector<double> u(10001);
    vector<int> X(10001);
    ifstream fin("data\\u2.dat");
    for (int i = 1; i <= 10000; i++)
        fin >> u[i];
    for (int i = 1; i <= 10000; i++) {
        if (u[i] < 0.20) X[i] = 1;
        else if (u[i] < 0.35) X[i] = 2;
        else if (u[i] < 0.60) X[i] = 3;
        else X[i] = 4;
    }
    ofstream fout("data\\Task4_X.dat");
    fout.tie(nullptr);
    for (int i = 1; i <= 10000; i++)
        fout << X[i] << " ";
    return 0;
}
