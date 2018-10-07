#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
ll N, M;
ll V[MAXN];
ll reg[2 * MAXN];
void buildr() {
    for (ll i = N - 1; i >= 0; i--)
        reg[i] = reg[i << 1] + reg[i << 1 | 1];
}

void modifyr(ll p, ll val) {
    for (reg[p += N] = val; p > 0; p >>= 1)
        reg[p >> 1] = reg[p] + reg[p ^ 1];
}

ll queryr(ll l, ll r) {
    ll res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += reg[l++];
        if (r & 1)
            res += reg[--r];
    }
    return res;
}

ll seg[2 * MAXN];
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

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> V[i];
    }
    for (ll i = 0; i < N; i++) {
        seg[i + N] = V[i];
    }
    sort(V, V + N);
    for (ll i = 0; i < N; i++) {
        reg[i + N] = V[i];
    }
    build();
    buildr();
    cin >> M;
    for (ll i = 0; i < M; i++) {
        ll t;
        ll l, r;
        cin >> t >> l >> r;
        l--;
        if (t == 1) {
            cout << query(l, r) << endl;
        } else {
            cout << queryr(l, r) << endl;
        }
    }
}