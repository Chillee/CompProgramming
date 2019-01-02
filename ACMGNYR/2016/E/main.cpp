#include <bits/stdc++.h>

using namespace std;

const int MOD = 1001113;
const int MAXN = 105;
int P, K, N, V;
int dp[MAXN][MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P;
    for (int p = 0; p < P; p++) {
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                dp[i][j] = 0;
        cin >> K >> N >> V;
        dp[0][0] = 1;
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j <= V; j++) {
                dp[i][j] = dp[i - 1][j] * (j + 1) + dp[i - 1][j - 1] * (i - j);
                dp[i][j] %= MOD;
            }
        }
        cout << K << ' ' << dp[N][V] << endl;
    }
}