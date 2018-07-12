#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
int N, M, K;
string S, T;
int dp[15][MAXN][MAXN][2];
int main() {
    cin >> N >> M >> K;
    cin >> S;
    cin >> T;
    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= M; k++) {
                if (S[j - 1] == T[k - 1]) {
                    dp[i][j][k][1] = max(dp[i][j][k][1], dp[i][j - 1][k - 1][1] + 1);
                    dp[i][j][k][1] = max(dp[i][j][k][1], dp[i - 1][j - 1][k - 1][0] + 1);
                }
                dp[i][j][k][0] = max(dp[i][j][k][0], dp[i][j - 1][k][0]);
                dp[i][j][k][0] = max(dp[i][j][k][0], dp[i][j - 1][k][1]);
                dp[i][j][k][0] = max(dp[i][j][k][0], dp[i][j][k - 1][0]);
                dp[i][j][k][0] = max(dp[i][j][k][0], dp[i][j][k - 1][1]);
            }
        }
    }
    cout << max(dp[K][N][M][0], dp[K][N][M][1]) << endl;
}