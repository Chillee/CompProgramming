#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
const ll MAXVAL = 2e9 + 5;
ll N, K, S, T;
ll C[MAXN], V[MAXN];
ll stops[MAXN];
ll dists[MAXN];
pair<ll, ll> cars[MAXN];
bool test(ll f) {
    ll curTime = 0;
    for (ll i = 0; i <= K; i++) {
        if (dists[i] > f) {
            curTime = MAXVAL;
            break;
        }
        curTime += (dists[i] * 2) - min(f - dists[i], dists[i]);
    }
    return curTime <= T;
}
ll binSearch(ll l, ll r) {
    if (l == r - 1) {
        for (ll i = max(1LL, l - 2); i <= r + 2; i++) {
            bool res = test(i);
            if (res) {
                return i;
            }
        }
        return l;
    }
    ll mid = (l + r) / 2;
    if (test(mid)) {
        return binSearch(l, mid);
    } else {
        return binSearch(mid, r);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K >> S >> T;
    for (ll i = 0; i < N; i++) {
        cin >> C[i] >> V[i];
    }
    for (ll i = 0; i < K; i++) {
        ll t;
        cin >> t;
        stops[i] = t;
    }
    sort(stops, stops + K);
    ll cur = 0;
    for (ll i = 0; i < K; i++) {
        dists[i] = (stops[i] - cur);
        cur = stops[i];
    }
    dists[K] = S - cur;
    ll minFuel = binSearch(0, MAXVAL);

    ll ans = MAXVAL;
    for (ll i = 0; i < N; i++) {
        if (V[i] >= minFuel) {
            ans = min(ans, C[i]);
        }
    }
    if (ans == MAXVAL) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}