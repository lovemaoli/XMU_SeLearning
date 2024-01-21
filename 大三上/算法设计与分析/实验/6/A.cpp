#include <bits/stdc++.h>
using namespace std;

const signed LEN = 4e6;

int n, m;
bool connect[32][32];

class compressedArray : private array<unsigned char, 6> {
public:
    compressedArray() {}

    int get(int i) {
        // --i;
        bool odd = i & 1;
        int p = i >> 1;
        if (odd)
            return ((*this)[p] >> 4);
        else
            return ((*this)[p] & 0x0f);
    }

    void set(int i, int value) {
        // --i;
        bool odd = i & 1;
        int p = i >> 1;
        if (odd)
            (*this)[p] = ((*this)[p] & 0x0f) | (value << 4);
        else
            (*this)[p] = ((*this)[p] & 0xf0) | value;
    }
};
compressedArray ans;

struct __node {
    int depth;
    compressedArray permutation;

    __node() {}

    __node(int depth) : depth(depth) {
        for (int i = 1; i <= n; ++i) {
            permutation.set(i, i);
            // cerr << debug(i) << permutation.get(i) << endl;
        }
    }

    __node(const __node& node) : depth(node.depth), permutation(node.permutation) {}

    int getMaxDis() {
        int res = 0;
        for (int j = 1; j <= m; ++j) {
            int l = n, r = 1;
            for (int i = 1; i <= n; ++i) {
                if (connect[permutation.get(i)][j]) {
                    l = min(l, i);
                    r = max(r, i);
                }
            }
            res = max<int>(res, r - l);
        }
        return res;
    }
};

class cqueue {
    signed head, tail;
    __node q[LEN];

public:
    cqueue() {
        head = 0;
        tail = 0;
    }

    void push(const __node& a) {
        q[tail++] = a;
        tail %= LEN;
    }

    void pop() {
        head++;
        head %= LEN;
    }

    __node front() {
        return q[head];
    }

    bool empty() {
        return head == tail;
    }
} q;

int BFS() {
    int res = n + 1;
    q.push(__node(0));
    while (!q.empty()) {
        __node temp = q.front();
        q.pop();

        if (temp.depth == n - 1) {
            int dis = temp.getMaxDis();
            if (dis < res) {
                res = dis;
                ans = temp.permutation;
            }
        } else {
            for (int i = temp.depth + 1; i <= n; ++i) {
                __node next(temp);
                next.depth++;
                int dis = next.getMaxDis();
                if (dis < res) {
                    int t = next.permutation.get(next.depth);
                    next.permutation.set(next.depth, next.permutation.get(i));
                    next.permutation.set(i, t);
                    q.push(next);
                }
            }
        }
    }
    return res;
}


int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            int temp;
            cin >> temp;
            connect[i][j] = temp;
        }
    cout << BFS() << endl;
    for(int i = 1; i <= n; ++i)
        cout << ans.get(i) << " ";
    return 0;
}


