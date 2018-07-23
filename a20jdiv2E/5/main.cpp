#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MAXBITS = 22;

ll N, M;
ll H;
ll A[MAXN];
ll seg[MAXBITS][2 * MAXN];
ll lazy[MAXBITS][2 * MAXN];
ll bit;

void apply(ll p, ll value, ll k) {
    if (value == 0) {
        return;
    }
    seg[bit][p] = (k - seg[bit][p]);
    if (p < N) {
        lazy[bit][p] ^= value;
    }
}

void propDown(ll p) {
    ll k = 1 << (H - 1);
    for (ll s = H; s > 0; s--, k >>= 1) {
        ll i = p >> s;
        if (lazy[i] != 0) {
            apply(i << 1, lazy[bit][i], k);
            apply(i << 1 | 1, lazy[bit][i], k);
            lazy[bit][i] = 0;
        }
    }
}

void propUp(ll p) {
    ll k = 2;
    while (p > 1) {
        p >>= 1;
        seg[bit][p] = seg[bit][p << 1] + seg[bit][p << 1 | 1];
        if (lazy[bit][p]) {
            seg[bit][p] = k - seg[bit][p];
        }
        k <<= 1;
    }
}

void inc(ll l, ll r, ll val) {
    l += N, r += N;
    ll l0 = l, r0 = r, k = 1;
    for (; l < r; l >>= 1, r >>= 1, k <<= 1) {
        if (l & 1)
            apply(l++, val, k);
        if (r & 1)
            apply(--r, val, k);
    }
    propUp(l0);
    propUp(r0 - 1);
}

ll query(ll l, ll r) {
    l += N, r += N;
    propDown(l);
    propDown(r - 1);
    ll res = 0;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            res += seg[bit][l++];
        }
        if (r & 1)
            res += seg[bit][--r];
    }
    return res;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    H = sizeof(ll) * 8 - __builtin_clzll(N);
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (bit = 0; bit < MAXBITS; bit++) {
        for (ll i = 0; i < N; i++) {
            seg[bit][i + N] = (A[i] & (1 << bit)) ? 1 : 0;
        }
    }
    for (bit = 0; bit < MAXBITS; bit++) {
        for (ll i = N; i < 2 * N; i++) {
            propUp(i);
        }
    }
    ll M;
    cin >> M;
    for (ll i = 0; i < M; i++) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll a, b;
            cin >> a >> b;
            a--, b--;
            ll ans = 0;
            for (bit = 0; bit < MAXBITS; bit++) {
                ans += query(a, b + 1) * (1 << bit);
            }
            cout << ans << endl;
        } else {
            ll a, b, x;
            cin >> a >> b >> x;
            a--, b--;
            for (bit = 0; bit < MAXBITS; bit++) {
                inc(a, b + 1, (x & (1 << bit)) ? 1 : 0);
            }
        }
    }
}