#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int mapp[105][105];
int path[105 * 105];
int best[105 * 105];

int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};
int p, q, r, s;
int minturn = 0x3f3f3f3f;
int num = 0;

void backtrack(int x, int y, int cur)
{
    if (cur >= n * m - k)
    {
        if (x != r || y != s)
            return;
        int turn = 0;
        for (int i = 2; i < cur; i++)
            if (path[i] != path[i - 1])
                turn++;
        if (turn < minturn)
        {
            memcpy(best, path, sizeof(path));
            minturn = turn;
            num = 1;
        }
        else if (turn == minturn)
            num++;
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (mapp[xx][yy] == -1)
            continue;
        if (xx < 1 || xx > n || yy < 1 || yy > m)
            continue;
        path[cur] = i;
        mapp[xx][yy] = -1;
        backtrack(xx, yy, cur + 1);
        mapp[xx][yy] = 0;
    }
}

void path_solve()
{
    int x = p, y = q;
    mapp[p][q] = 1;
    for (int i = 1; i < n * m - k; i++)
    {
        int xx = x + dx[best[i]];
        int yy = y + dy[best[i]];
        mapp[xx][yy] = mapp[x][y] + 1;
        x = xx;
        y = yy;
    }
}

int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++)
    {
        int x, y;
        cin >> x >> y;
        mapp[x][y] = -1;
    }
    cin >> p >> q >> r >> s;
    mapp[p][q] = -1;
    backtrack(p, q, 1);
    path_solve();
    cout << minturn << endl;
    cout << num << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j != 1)
                cout << " ";
            cout << mapp[i][j];
        }
        cout << endl;
    }
}