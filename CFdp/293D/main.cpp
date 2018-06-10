#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
int N, T;
long double P;
long double dp[MAXN][MAXN];
int main() {
    cin >> N >> P >> T;
    dp[0][0] = 1;
    for (int i = 1; i <= T; i++) {
        for (int j = 0; j <= N; j++) {
            if (j == N) {
                dp[i][j] = dp[i - 1][j];
                dp[i][j] += dp[i - 1][j - 1] * P;
            } else if (j == 0) {
                dp[i][j] += dp[i - 1][j] * (1 - P);
            } else if (j != 0) {
                dp[i][j] += dp[i - 1][j - 1] * P;
                dp[i][j] += dp[i - 1][j] * (1 - P);
            }
        }
    }
    long double ans = 0;
    for (int i = 0; i <= N; i++) {
        ans += dp[T][i] * i;
    }
    cout << fixed << setprecision(10);
    cout << ans << endl;
}