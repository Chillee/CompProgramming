#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;
const int INF = 1e9 + 5;
int N;
int dp[MAXN][MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            dp[i][j] = INF;

    cin >> N;
    for (int i = 0; i < N; i++) {
        dp[i][i + 1] = 0, dp[i][i] = 0;
    }
    for (int i = 0; i < N; i++)
        dp[i][i + 2] = (i + 1) * (i + 2) * (i + 3);
    for (int l = 3; l < N; l++) {
        for (int i = 0; i < N - l; i++) {
            for (int j = i + 2; j < i + l; j++) {
                // cout << i << ' ' << i + l << " " << j << endl;
                dp[i][i + l] = min(dp[i][i + l], dp[i][j] + dp[j][i + l] + (i + 1) * (j + 1) * (j + 2));
            }
        }
    }
    cout << dp[0][N - 1] << endl;
}