#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 5e3 + 5;
const ll INF = 1e18 + 5;
ll N;
ll dp[MAXN][MAXN];
ll A[MAXN];
ll calc(ll l, ll r) {
    if (dp[l][r] != INF)
        return dp[l][r];
    if (l + r == N) {
        dp[l][r] = 0;
        return dp[l][r];
    }
    if ((l + r) % 2 == 0) {
        dp[l][r] = -INF;
        if (l != N)
            dp[l][r] = max(dp[l][r], calc(l + 1, r) + A[l]);
        if (r != N)
            dp[l][r] = max(dp[l][r], calc(l, r + 1) + A[N - r - 1]);
    } else {
        dp[l][r] = INF;
        if (l != N)
            dp[l][r] = min(dp[l][r], calc(l + 1, r));
        if (r != N)
            dp[l][r] = min(dp[l][r], calc(l, r + 1));
    }
    return dp[l][r];
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++)
        cin >> A[i];
    for (ll i = 0; i < MAXN; i++)
        for (ll j = 0; j < MAXN; j++)
            dp[i][j] = INF;
    calc(0, 0);
    // for (ll i = 0; i < N; i++) {
    //     for (ll j = 0; j < N; j++)
    //         cout << dp[i][j] << ' ';
    //     cout << endl;
    // }
    cout << dp[0][0] << endl;
}