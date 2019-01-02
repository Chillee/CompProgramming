#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 5;
int P, K, M, N;
int dp[MAXN][105];
int binExp(int base, int exp) {
    if (exp == 0)
        return 1;
    return binExp(base * base, exp / 2) * (exp % 2 == 1 ? base : 1);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P;
    for (int p = 0; p < P; p++) {
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < 105; j++)
                dp[i][j] = 0;
        cin >> K >> M >> N;
        dp[0][0] = 1;
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < 10; j++) {
                if (binExp(M, j) > i)
                    break;
                for (int k = 0; k <= j; k++) {
                    dp[i][j] += dp[i - binExp(M, j)][k];
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < 10; i++) {
            ans += dp[N][i];
        }
        cout << K << ' ' << ans << endl;
    }
}