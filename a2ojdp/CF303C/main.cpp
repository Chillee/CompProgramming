#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll MAXN = 1e5 + 5;
const ll INF = 2e18;
typedef pair<ll, ll> pii;
ll N;
ll X[MAXN];
ll H[MAXN];
ll dp[MAXN][3];

int main() {
    for (ll i = 0; i < MAXN; i++) {
        for (ll j = 0; j < 3; j++) {
            dp[i][j] = -INF;
        }
    }
    // fill(dp, -(1 << 30));
    cin >> N;
    for (ll i = 1; i <= N; i++) {
        cin >> X[i] >> H[i];
    }
    X[0] = -INF;
    X[N + 1] = INF;
    dp[0][0] = dp[0][1] = dp[0][2] = 0;
    for (ll i = 1; i <= N; i++) {
        for (ll j = 0; j <= 2; j++) {
            ll l = X[i], r = X[i];
            if (j == 0)
                l = X[i] - H[i];
            else if (j == 2)
                r = X[i] + H[i];
            // cout << i << ' ' << j << ' ' << l << ' ' << r << endl;
            // cout << X[i - 1] << ' ' << X[i + 1] << endl;
            if (l > X[i - 1] && r < X[i + 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][1]);
            }
            if (l > X[i - 1] + H[i - 1] && r < X[i + 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][2]);
            }
            if (l > X[i - 1] && r < X[i + 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][0]);
            }
            if (j == 0 || j == 2)
                dp[i][j]++;
        }
    }
    ll res = 0;
    for (ll i = 0; i <= N; i++) {
        for (ll j = 0; j < 3; j++) {
            res = max(res, dp[i][j]);
        }
    }
    cout << res << endl;
}