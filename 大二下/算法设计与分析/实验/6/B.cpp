#include <iostream>
#include <algorithm>
#include <cstring>

#define SIZE 102

using namespace std;

int a[SIZE], s[SIZE] = {0}, n, k;

bool cmp(int a, int b) {
	return (a > b);
}

bool dfs(int x, int mid) { // 深搜判定
	int i;

	if (x > n) { // 全部做完,可以
		return true;
	}

	for (i = 1; i <= k; i++) {
		if (a[x] > mid) { // 大于限定时间,不成
			return false;
		}

		s[i] += a[x];

		if (s[i] <= mid) {
			if (dfs(x + 1, mid)) { // 只要有一个分支搜索成立
				return true; // 那么这个搜索就成立
			}
		}
		s[i] -= a[x];
	}

	return false;
}

int main(int argc, char** argv) {
	int i, sum = 0, l, r, res, mid;

	cin >> n >> k;
	for (i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
	}

	sort(a + 1, a + n + 1, cmp);

	l = sum / k;
	r = sum;
	while (l <= r) { // 哇哇哇,又是二分答案
		mid = l + (r - l) / 2; // 防溢出专用
		memset(s, 0, sizeof(s));
		if (dfs(1, mid)) {
			res = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}

	cout << res << endl;

	return 0;
}
