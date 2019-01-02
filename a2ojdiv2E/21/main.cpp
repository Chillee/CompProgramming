#include <bits/stdc++.h>

using namespace std;

const int MAXN = 605;
int N;
int L[MAXN], R[MAXN];
int dp[MAXN][MAXN];
string ans[MAXN][MAXN];
bool calc(int l, int r) {
    if (dp[l][r] != -1)
        return dp[l][r];
    if (l > r) {
        return false;
    }
    if (l == r) {
        if (L[l] <= 1 && R[l] >= 1) {
            dp[l][r] = true;
            ans[l][r] = "()";
        } else {
            dp[l][r] = false;
        }
        return dp[l][r];
    }
    for (int i = L[l]; i <= R[l]; i++) {
        if (i % 2 == 0)
            continue;
        int cnt = i / 2;
        bool res;
        string cur;
        if (cnt == 0) {
            res = calc(l + 1, r);
            cur = "()" + ans[l + 1][r];
        } else if (l + cnt == r) {
            res = calc(l + 1, r);
            cur = "(" + ans[l + 1][r] + ")";
        } else if (l + cnt + 1 > r) {
            continue;
        } else {
            res = calc(l + 1, l + cnt) && calc(l + cnt + 1, r);
            cur = "(" + ans[l + 1][l + cnt] + ")" + ans[l + cnt + 1][r];
        }
        if (res) {
            dp[l][r] = true;
            ans[l][r] = cur;
            return true;
        }
    }
    dp[l][r] = false;
    return false;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> L[i] >> R[i];
    }
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            dp[i][j] = -1;
        }
    }
    calc(0, N - 1);
    if (dp[0][N - 1] == 1) {
        cout << ans[0][N - 1] << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}