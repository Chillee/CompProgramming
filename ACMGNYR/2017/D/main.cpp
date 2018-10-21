#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 1e5 + 5;
const int NUMSTATES = 5;
int P, K, N;
int dp[MAXN][NUMSTATES];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P;
    for (int t = 0; t < P; t++) {
        cin >> K >> N;
        for (int i = 0; i < MAXN; i++) {
            for (int k = 0; k < NUMSTATES; k++) {
                dp[i][k] = 0;
            }
        }
        dp[1][4] = 1;
        for (int i = 2; i < N + 2; i++) {
            dp[i][0] = dp[i - 1][3] + dp[i - 2][4];
            dp[i][1] = dp[i - 1][2] + dp[i - 2][4];
            dp[i][2] = dp[i - 1][4] + dp[i][0] + dp[i - 1][3] + dp[i - 2][4];
            dp[i][3] = dp[i - 1][4] + dp[i][1] + dp[i - 1][2] + dp[i - 2][4];
            dp[i][4] = dp[i][2] + dp[i][3] + dp[i][0] + dp[i][1] + dp[i - 1][2] + dp[i - 1][3];
        }
        for (int j = 0; j < N + 2; j++) {
            for (int i = 0; i < 5; i++) {
                cout << dp[j][i] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
}