#include <bits/stdc++.h>

using namespace std;

const int MAXN = 405;
int N, K;
void out(double x) {
    cout << fixed << setprecision(20) << x << endl;
    exit(0);
}
double dp[MAXN][MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    dp[0][0] = 1;
    for (int i = 1; i <= K; i++) {
        for (int j = 0; j <= N; j++) {
            if (j != N - 1) {
                dp[i][j] = dp[i - 1][j] * 0.5 + (j == 0 ? 0 : dp[i - 1][j - 1] * .5);
            } else if (j == N - 1) {
                dp[i][j] = dp[i - 1][j] * 0.5 + dp[i - 1][j - 1] * 0.5 + dp[i - 1][N] * 0.5;
            }
        }
    }
    double ans = 0;
    for (int i = 0; i <= N; i++) {
        ans += dp[K][i] * i;
    }
    out(ans);
}