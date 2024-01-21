#include <bits/stdc++.h>
using namespace std;
#define For(i, a, b) for (int i = (a), _##i = (b); i < _##i; ++i)
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define Forr(i, a, b) for (int i = (a), _##i = (b); i > _##i; --i)
#define FORR(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define all(a) a.begin(), a.end()
#define range(i, a) for (auto& i : a)
#define RANGE(i, a) for (auto i = a.rbegin(); i != a.rend(); ++i)
#define debug(a) #a << " = " << (a) << '\t'
// #define int ll
using ll = long long;
using pii = pair<int, int>;
using pdd = pair<double, double>;

namespace Solver {
    const int N = 32;
    int n;
    int conn[N][N];
    vector<int> ans;
    int mincost = INT_MAX;
    vector<int> stk;
    bool used[N];

    void DFS(int cnt, int cost) {
        if (cnt > n) {
            if (cost < mincost) {
                mincost = cost;
                ans = stk;
            }
            return;
        }
        FOR (i, cnt, n) {
            swap(stk[cnt], stk[i]);
            int temp = cost;
            For (j, 1, cnt)
                temp += conn[j][cnt] * abs(stk[j] - stk[cnt]);
            DFS(cnt + 1, temp);
            swap(stk[cnt], stk[i]);
        }
    }

    void main(int T) {
        cin >> n;
        stk.resize(n + 1);
        iota(stk.begin() + 1, stk.end(), 1);
        FOR (i, 1, n)
            FOR (j, i + 1, n)
                cin >> conn[i][j];
        DFS(1, 0);

        cout << mincost << endl;
        FOR (i, 1, n)
            cout << ans[i] << ' ';
        cout << endl;
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int T = 1;
    // cin >> T;
    FOR (t, 1, T)
        Solver::main(t);
    return 0;
}