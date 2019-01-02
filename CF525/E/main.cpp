#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 3e5 + 5;
ll A[MAXN];
vector<ll> adj[MAXN];
vector<ll> child[MAXN];
ll dp[MAXN];

void root(ll cur, ll par) {
    for (auto i : adj[cur]) {
        if (i == par)
            continue;
        child[cur].push_back(i);
        root(i, cur);
    }
}
void calc(ll cur) {
    for (auto i : child[cur]) {
        calc(i);
    }
    dp[cur] = A[cur];
    for (auto i : child[cur]) {
        if (dp[i] > 0) {
            dp[cur] += dp[i];
        }
    }
}
ll mx = -1e9;
ll ans = 0;
void count(ll cur) {
    for (auto i : child[cur]) {
        count(i);
    }
    dp[cur] = A[cur];
    for (auto i : child[cur]) {
        if (dp[i] > 0) {
            dp[cur] += dp[i];
        }
    }
    if (dp[cur] == mx) {
        dp[cur] = 0;
        ans++;
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N;
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (ll i = 0; i < N - 1; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    root(0, -1);
    calc(0);
    for (ll i = 0; i < N; i++) {
        mx = max(mx, dp[i]);
    }
    fill(begin(dp), end(dp), 0);
    count(0);
    cout << mx * ans << ' ' << ans << endl;
}