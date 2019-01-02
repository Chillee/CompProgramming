#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
int dp[32][32][52];
int dfs(int n, int m, int k) {
    if (dp[n][m][k] != -1) {
        return dp[n][m][k];
    }
    if (k == n * m || k == 0) {
        dp[n][m][k] = 0;
        return 0;
    }
    if (k > n * m) {
        dp[n][m][k] = INF;
        return dp[n][m][k];
    }
    int res = INF;
    for (int i = 1; i < n; i++) {
        for (int c = 1; c <= k; c++) {
            res = min(res, dfs(i, m, c) + dfs(n - i, m, k - c) + m * m);
        }
    }
    for (int i = 1; i < m; i++) {
        for (int c = 1; c <= k; c++) {
            res = min(res, dfs(n, i, c) + dfs(n, m - i, k - c) + n * n);
        }
    }
    dp[n][m][k] = res;
    return res;
}
int main() {
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 31; j++) {
            for (int k = 0; k < 51; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int n, m, k;
        cin >> n >> m >> k;
        cout << dfs(n, m, k) << endl;
    }
}