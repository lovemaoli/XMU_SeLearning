#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    vector<double> x(10001), y(10001), z(10001), u(10001);
    x[0] = 1;
    y[0] = 233;
    z[0] = 114514;
    for (int i = 1; i <= 10000; i++) {
        x[i] = fmod(171 * x[i - 1], 30269);
        y[i] = fmod(170 * y[i - 1], 30307);
        z[i] = fmod(172 * z[i - 1], 30323);
    }
    for (int i = 1; i <= 10000; i++)
        u[i] = fmod(x[i] / 30269 + y[i] / 30307 + z[i] / 30323, 1);
    ofstream fout("data\\u2.dat");
    fout.tie(nullptr);
    for (int i = 1; i <= 10000; i++)
        fout << u[i] << " ";
    return 0;
}
