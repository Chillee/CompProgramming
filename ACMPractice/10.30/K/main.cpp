#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e3 + 5;
int N, M;
int A[MAXN];
int dp[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        int hi = 0, cntl = 0, cnth = 0;
        for (int j = i; j >= 0; j--) {
            if (A[j] >= M)
                cnth++;
            else
                cntl++;
            if (cnth >= cntl + 1) {
                hi = max(hi, j == 0 ? 1 : (dp[j - 1] > 0 ? 1 + dp[j - 1] : 0));
            }
        }
        dp[i] = hi;
    }
    cout << dp[N - 1] << endl;
}