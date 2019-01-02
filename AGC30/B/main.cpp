
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
int L;
int N;
int X[MAXN];
int dp[MAXN][MAXN][2];
int distR(int a, int b) { return ((b - a) + L) % L; }
int distL(int a, int b) { return ((a - b) + L) % L; }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> L >> N;

    for (int i = 1; i <= N; i++)
        cin >> X[i];
    X[0] = 0;
    X[N + 1] = 0;
    dp[0][0][0] = dp[0][0][1] = 0;
    for (int i = 1; i <= N; i++)
        dp[0][i][1] = dp[0][i - 1][1] + distR(X[i - 1], X[i]);
    for (int i = 1; i <= N; i++)
        dp[i][0][0] = dp[i - 1][0][0] + distL(X[N - i + 1], X[N - i]);
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; i + j <= N; j++) {
            dp[i][j][0] = max(dp[i - 1][j][0] + distL(X[N - (i - 2)], X[N - i + 1]), dp[i - 1][j][1] + distL(X[N - j + 1], X[N - i + 1]));
            dp[i][j][1] = max(dp[i][j - 1][0] + distR(X[i], X[j]), dp[i][j - 1][1] + distR(X[j - 1], X[j]));
            // max(dp[i][j - 1] + distR(X[j - 1], X[j]), dp[i - 1][j] + distL(X[N - i + 1], X[N - i]));
            ans = max(dp[i][j][0], ans);
            ans = max(dp[i][j][1], ans);
        }
    }
    // for (int i = 0; i <= N; i++) {
    //     for (int j = 0; j <= N; j++)
    //         cout << dp[i][j][0] << " ";
    //     cout << endl;
    // }
    cout << ans << endl;
}