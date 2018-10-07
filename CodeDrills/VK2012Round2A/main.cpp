#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;
string S, T;
int dp[MAXN][MAXN];
int last[26];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S >> T;
    for (int i = 0; i < S.size(); i++) {
        fill(last, last + 26, -1);
        for (int j = 0; j < T.size(); j++) {
            if (S[i] == T[j]) {
                if (i == 0) {
                    dp[i][j] = 1;
                } else if (last[S[i - 1] - 'a'] != -1)
                    dp[i][j] += dp[i - 1][last[S[i - 1] - 'a']];
            }
            if (last[T[j] - 'a'] != -1) {
                dp[i][j] += dp[i][last[T[j] - 'a']];
            }
            last[T[j] - 'a'] = j;
        }
    }
    for (int i = 0; i < S.size(); i++) {
        for (int j = 0; j < T.size(); j++) {
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }
}