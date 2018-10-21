#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
const ll MAXN = 1e3 + 5;
const ll MAXB = 1e4 + 5;
// const ll MAXB = 15;
const ll INF = 1e9 + 5;
ll N, W, B, X;
ll A[MAXN];
ll C[MAXN];
ll dp[MAXN][MAXB];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> W >> B >> X;
    for (ll i = 1; i <= N; i++) {
        cin >> A[i];
    }
    for (ll i = 1; i <= N; i++) {
        cin >> C[i];
    }
    for (ll i = 0; i < MAXN; i++)
        for (ll j = 0; j < MAXB; j++)
            dp[i][j] = -INF;

    dp[0][0] = W;
    for (ll i = 1; i <= N; i++) {
        priority_queue<array<ll, 2>> pq;
        for (ll j = 0; j < MAXB; j++) {
            pq.push({min(dp[i - 1][j] + X, W + j * B) + C[i] * j, j});
            while (!pq.empty() && (pq.top()[1] < j - A[i] || pq.top()[1] > j)) {
                pq.pop();
            }
            if (pq.size() > 0) {
                dp[i][j] = pq.top()[0] - C[i] * j;
            }
            if (dp[i][j] < 0) {
                dp[i][j] = -INF;
                break;
            }
        }
    }
    ll ans = 0;
    for (ll i = 0; i <= N; i++) {
        for (ll j = 0; j < MAXB; j++) {
            // cout << dp[i][j] << ' ';
            // ;
            if (dp[i][j] >= 0)
                ans = max(ans, j);
        }
        // cout << endl;
    }
    cout << ans << endl;
}