#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll INF = 1e18 + 5;
ll N;
string S;
ll dp[MAXN][5];
ll A[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> S;
    S = "$" + S;
    for (ll i = 1; i <= N; i++)
        cin >> A[i];
    dp[0][0] = 0;
    dp[0][1] = INF;
    dp[0][2] = INF;
    dp[0][3] = INF;
    dp[0][4] = INF;
    for (ll i = 1; i < S.size(); i++) {
        for (ll j = 0; j < 5; j++)
            dp[i][j] = dp[i - 1][j];
        if (S[i] == 'h') {
            dp[i][1] = min(dp[i][0], dp[i][1]);
            dp[i][0] += A[i];
        } else if (S[i] == 'a') {
            dp[i][2] = min(dp[i][1], dp[i][2]);
            dp[i][1] += A[i];
        } else if (S[i] == 'r') {
            dp[i][3] = min(dp[i][2], dp[i][3]);
            dp[i][2] += A[i];
        } else if (S[i] == 'd') {
            dp[i][3] += A[i];
        }
    }
    ll ans = INF;
    for (ll i = 0; i < 4; i++) {
        ans = min(ans, dp[S.size() - 1][i]);
    }
    cout << ans << endl;
}