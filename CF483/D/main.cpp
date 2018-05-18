#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e3 + 5;
int N, Q;
int dp[MAXN][MAXN];
int pre[MAXN][MAXN];
int A[MAXN];
int f(int l, int r) {
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    if (l == r - 1) {
        dp[l][r] = A[l];
    } else {
        dp[l][r] = f(l, r - 1) ^ f(l + 1, r);
    }
    return dp[l][r];
}
int pref(int l, int r) {
    if (pre[l][r] != -1) {
        return pre[l][r];
    }
    pre[l][r] = dp[l][r];
    if (l != r - 1) {
        pre[l][r] = max(pre[l][r], pref(l + 1, r));
        pre[l][r] = max(pref(l, r - 1), pre[l][r]);
    }
    return pre[l][r];
}
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            dp[i][j] = -1;
            pre[i][j] = -1;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j <= N; j++) {
            f(i, j);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j <= N; j++) {
            pref(i, j);
        }
    }
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        cout << pre[a - 1][b] << endl;
    }
}