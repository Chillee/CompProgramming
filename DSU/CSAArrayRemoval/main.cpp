#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
ll N;
ll A[MAXN];
ll P[MAXN];
bool usable[MAXN];
ll par[MAXN];
ll root(ll x) { return (par[x] <= 0 ? x : (par[x] = root(par[x]))); }
ll merge(ll a, ll b) {
    if ((a = root(a)) == (b = root(b)))
        return abs(par[a]);
    if (par[a] > par[b])
        swap(a, b);
    par[a] += par[b];
    par[b] = a;
    return abs(par[a]);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 1; i <= N; i++) {
        cin >> A[i];
    }
    for (ll i = 0; i < N; i++) {
        cin >> P[i];
    }
    for (ll i = 1; i <= N; i++) {
        par[i] = -A[i];
    }
    ll mxSum = 0;
    vector<ll> ans;
    for (ll i = N - 1; i >= 0; i--) {
        usable[P[i]] = true;
        mxSum = max(mxSum, A[P[i]]);
        if (P[i] - 1 > 0 && usable[P[i] - 1])
            mxSum = max(mxSum, merge(P[i], P[i] - 1));
        if (P[i] + 1 <= N && usable[P[i] + 1])
            mxSum = max(mxSum, merge(P[i], P[i] + 1));
        ans.push_back(mxSum);
    }
    for (ll i = N - 1; i >= 0; i--) {
        cout << ans[i] << endl;
    }
}