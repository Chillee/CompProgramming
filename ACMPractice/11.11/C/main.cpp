#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 998244353;
const ll MAXN = 1e3 + 5;
ll dp[MAXN][MAXN];
ll N, K;
map<ll, ll> cnts;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (ll i = 0; i < N; i++) {
        ll d;
        cin >> d;
        cnts[d]++;
    }
    vector<ll> c;
    for (auto i : cnts) {
        c.push_back(i.second);
    }
    for (ll i = 0; i <= c.size(); i++)
        dp[i][0] = 1;
    for (ll i = 1; i <= c.size(); i++) {
        for (ll j = 1; j <= K; j++) {
            dp[i][j] = (i < j ? 0 : (dp[i - 1][j] + c[i - 1] * dp[i - 1][j - 1]));
            dp[i][j] %= MOD;
        }
    }
    cout << dp[c.size()][K] << endl;
}