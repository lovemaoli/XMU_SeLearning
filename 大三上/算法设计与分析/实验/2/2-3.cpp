#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 101;

int dp[MAXN][MAXN];

int main() {
    int n;
    cin >> n;

    vector<vector<int>> triangle(n, vector<int>(n, 0));

    // 读取数字三角形
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> triangle[i][j];
        }
    }

    // 初始化dp数组，dp[i][j]表示从顶到(i, j)的最大路径和
    dp[0][0] = triangle[0][0];

    // 动态规划计算最大路径和
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) {
                dp[i][j] = dp[i - 1][j] + triangle[i][j];  // 左边的路径
            } else if (j == i) {
                dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];  // 右边的路径
            } else {
                dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];  // 两个路径中选择较大者
            }
        }
    }

    // 找出最大路径和
    int maxSum = dp[n - 1][0];
    for (int j = 1; j < n; j++) {
        maxSum = max(maxSum, dp[n - 1][j]);
    }

    // 输出最大路径和
    cout << maxSum << endl;

    return 0;
}

