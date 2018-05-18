#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 5;
const int MAXM = 10;
int P, M, N, K;

int dp[MAXN][MAXM];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P;
    for (int t = 0; t < P; t++) {
        cin >> K >> M >> N;
        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXM; j++) {
                dp[i][j] = 0;
            }
        }
        dp[0][0] = 1;
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < MAXM; j++) {
                int pw = pow(M, j);
                if (i - pw < 0) {
                    break;
                }
                for (int k = 0; k <= j; k++) {
                    dp[i][j] += dp[i - pw][k];
                }
            }
        }
        // for (int i = 1; i <= N; i++) {
        //     for (int j = 0; j < MAXM; j++) {
        //         cout << dp[i][j] << ' ';
        //     }
        //     cout << endl;
        // }
        int sum = 0;
        for (int i = 0; i < MAXM; i++) {
            sum += dp[N][i];
        }
        cout << K << " " << sum << endl;
        // return 0;
    }
}