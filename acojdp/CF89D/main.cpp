#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e8;
const int MAXN = 105;
const int MAXK = 12;

int N1, N2, K1, K2;

int dp[MAXN][MAXN][2][MAXK];
int main() {
    cin >> N1 >> N2 >> K1 >> K2;
    dp[0][0][0][0] = 1;
    for (int i = 0; i <= N1; i++) {
        for (int j = 0; j <= N2; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 1; l < MAXK; l++) {
                    if (l == 1 && k == 0 && i != 0) {
                        for (int m = 0; m <= K2; m++) {
                            dp[i][j][k][l] = (dp[i][j][k][l] + dp[i - 1][j][1][m]) % MOD;
                        }
                    } else if (l == 1 && k == 1 && j != 0) {
                        for (int m = 0; m <= K1; m++) {
                            dp[i][j][k][l] = (dp[i][j][k][l] + dp[i][j - 1][0][m]) % MOD;
                        }
                    }
                    if (k == 0 && i != 0) {
                        dp[i][j][k][l] = (dp[i][j][k][l] + dp[i - 1][j][k][l - 1]) % MOD;
                    } else if (k == 1 && j != 0) {
                        dp[i][j][k][l] = (dp[i][j][k][l] + dp[i][j - 1][k][l - 1]) % MOD;
                    }
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i <= K1; i++) {
        res = (res + dp[N1][N2][0][i]) % MOD;
    }
    for (int i = 0; i <= K2; i++) {
        res = (res + dp[N1][N2][1][i]) % MOD;
    }
    cout << res << endl;
}