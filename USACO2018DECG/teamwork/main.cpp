#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 5;
const int MAXK = 1e3 + 5;
int N, K;
int A[MAXN];
int dp[MAXN][MAXK];
int mxdp[MAXN];
int mxel[MAXN][MAXK];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXK; j++)
            dp[i][j] = -1e9;
    dp[0][0] = 0;
    mxdp[0] = 0;
    for (int i = 1; i <= N; i++) {
        dp[i][0] = mxdp[i - 1];
        dp[i][1] = mxdp[i - 1] + A[i];
        mxel[i][1] = A[i];
        mxdp[i] = max(dp[i][0], dp[i][1]);
        for (int j = 2; j <= K; j++) {
            if (dp[i - 1][j - 1] < 0)
                continue;
            mxel[i][j] = max(mxel[i - 1][j - 1], A[i]);
            dp[i][j] = dp[i - j + 1][0] + mxel[i][j] * j;
            mxdp[i] = max(mxdp[i], dp[i][j]);
        }
    }
    cout << mxdp[N] << endl;
}