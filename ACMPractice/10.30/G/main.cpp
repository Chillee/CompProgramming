#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
ll N, K;
struct seg {
    ll seg[2 * MAXN] = {0};
    void build() {
        for (ll i = N - 1; i >= 0; i--)
            seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }

    void modify(ll p, ll val) {
        for (seg[p += N] = val; p > 0; p >>= 1)
            seg[p >> 1] = seg[p] + seg[p ^ 1];
    }

    ll query(ll l, ll r) {
        ll res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res += seg[l++];
            if (r & 1)
                res += seg[--r];
        }
        return res;
    }
};
array<ll, 2> A[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    array<ll, 2> val = {0, 0};
    fill(begin(A), end(A), val);
    cin >> N >> K;
    for (ll i = 0; i < N; i++) {
        ll a;
        cin >> a;
        A[i] = {a, i};
    }
    sort(A, A + N);
    seg sms[2], cnts[2];
    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        ll l = A[i][1] - K + 1;
        ll r = A[i][1] + K;
        if (A[i][1] < K - 1) {
            l = K - A[i][1] - 1;
        }
        if (A[i][1] >= N - K + 1) {
            ll diff = N - A[i][1];
            r = N - K + diff;
        }
        l = max(l, 0ll);
        r = min(r, N);
        ll sm = sms[(A[i][1] + K + 1) % 2].query(l, r);
        ll cnt = cnts[(A[i][1] + K + 1) % 2].query(l, r);
        // cout << "i: " << A[i][0] << ' ' << A[i][1] << endl;
        // cout << l << ' ' << r << endl;
        // cout << sm << ' ' << cnt << endl;
        // cout << endl;
        ans += A[i][0] * cnt - sm;
        sms[A[i][1] % 2].modify(A[i][1], A[i][0]);
        cnts[A[i][1] % 2].modify(A[i][1], 1);
    }
    cout << ans << endl;
}