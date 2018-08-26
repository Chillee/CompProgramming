#include <bits/stdc++.h>

using namespace std;

const int N = 4;
int dp[1 << N][N];
int A[1 << N];
int F[1 << N];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < (1 << N); i++) {
        A[i] = i;
    }
    for (int mask = 0; mask < (1 << N); ++mask) {
        dp[mask][-1] = A[mask];
        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i))
                dp[mask][i] = dp[mask][i - 1] + dp[mask ^ (1 << i)][i - 1];
            else
                dp[mask][i] = dp[mask][i - 1];
        }
        F[mask] = dp[mask][N - 1];
    }
    for (int i = 0; i < (1 << N); i++) {
        cout << F[i] << ' ';
    }
    cout << endl;
}