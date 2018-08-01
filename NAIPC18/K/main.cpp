#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll MAXN = 100005;

typedef struct range {
    ll r;
    ll l;
    ll u;
    ll d;
    ll r2;
    ll l2;
    ll u2;
    ll d2;
    bool ldsolo;
    bool lusolo;
    bool rdsolo;
    bool rusolo;
} range;

ll N, Q;
range t[2 * MAXN];
const ll INF = 1e10;

range initialize() {
    range res;
    res.l = INF;
    res.r = -INF;
    res.u = -INF;
    res.d = INF;
    res.l2 = INF;
    res.r2 = -INF;
    res.u2 = -INF;
    res.d2 = INF;
    res.ldsolo = false;
    res.lusolo = false;
    res.rdsolo = false;
    res.rusolo = false;
    return res;
}
range update(range a, range b) {
    range c = initialize();
    // cout << a.r << ' ' << b.r << endl;
    // cout << a.r2 << ' ' << b.r2 << endl;
    vector<ll> rs = {a.r, b.r, a.r2, b.r2};
    vector<ll> ls = {a.l, b.l, a.l2, b.l2};
    vector<ll> us = {a.u, b.u, a.u2, b.u2};
    vector<ll> ds = {a.d, b.d, a.d2, b.d2};
    sort(rs.begin(), rs.end(), greater<ll>());
    sort(ls.begin(), ls.end());
    sort(us.begin(), us.end(), greater<ll>());
    sort(ds.begin(), ds.end());
    // cout << "arr: ";
    // for (auto i : rs) {
    //     cout << i << ' ';
    // }
    // cout << endl;
    c.r = rs[0];
    c.l = ls[0];
    c.u = us[0];
    c.d = ds[0];
    c.r2 = rs[1];
    c.l2 = ls[1];
    c.u2 = us[1];
    c.d2 = ds[1];
    if (a.ldsolo && a.l == c.l && a.d == c.d || b.ldsolo && b.l == c.l && b.d == c.d) {
        c.ldsolo = true;
    }
    if (a.lusolo && a.l == c.l && a.u == c.u || b.lusolo && b.l == c.l && b.u == c.u) {
        c.lusolo = true;
    }
    if (a.rdsolo && a.r == c.r && a.d == c.d || b.rdsolo && b.r == c.r && b.d == c.d) {
        c.rdsolo = true;
    }
    if (a.rusolo && a.r == c.r && a.u == c.u || b.rusolo && b.r == c.r && b.u == c.u) {
        c.rusolo = true;
    }
    return c;
}
void build() { // build the tree
    for (ll i = N - 1; i > 0; --i) {
        range l = t[i << 1];
        range r = t[i << 1 | 1];
        t[i] = update(l, r);
    }
}

range query(ll l, int r) {
    range res = initialize();
    ;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            range cur = t[l++];
            res = update(res, cur);
        }
        if (r & 1) {
            range cur = t[--r];
            res = update(res, cur);
        }
    }
    return res;
}

int main() {
    // freopen("input.txt", "r", stdin);
    cin >> N >> Q;
    for (ll i = 0; i < 2 * MAXN; i++) {
        t[i] = initialize();
    }

    for (ll i = 0; i < N; i++) {
        ll x, y;
        cin >> x >> y;
        t[i + N].l = x;
        t[i + N].r = x;
        t[i + N].u = y;
        t[i + N].d = y;
        t[i + N].ldsolo = true;
        t[i + N].lusolo = true;
        t[i + N].rdsolo = true;
        t[i + N].rusolo = true;
    }
    build();
    for (ll i = 0; i < Q; i++) {
        ll l, r;
        cin >> l >> r;
        l--;
        range res = query(l, r);
        ll mn = INF;
        ll xd = max(res.r - res.l, ll(0));
        ll yd = max(res.u - res.d, ll(0));
        ll xdl = max(res.r - res.l2, ll(0));
        ll xdr = max(res.r2 - res.l, ll(0));
        ll ydu = max(res.u2 - res.d, ll(0));
        ll ydd = max(res.u - res.d2, ll(0));
        ll xlength = min(xdl, xdr);
        ll ylength = min(ydu, ydd);
        ll ans = min(max(xlength, yd), max(ylength, xd));
        if (res.rdsolo) {
            ans = min(ans, max(xdr, ydd));
        }
        if (res.ldsolo) {
            ans = min(ans, max(xdl, ydd));
        }
        if (res.rusolo) {
            ans = min(ans, max(xdr, ydu));
        }
        if (res.lusolo) {
            ans = min(ans, max(xdl, ydu));
        }
        cout << ans << endl;
    }
}