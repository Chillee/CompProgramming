#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const ll RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    ll operator()(ll x) const { return hash_f(x); }
};
struct phash {
    ll operator()(pair<ll, ll> x) const { return hash_combine(hash_f(x.first), hash_f(x.second)); }
};
struct seg {
    ll N = 1e9 + 5;
    gp_hash_table<ll, ll, chash> seg;

    ll get(ll x) { return (seg.find(x) == seg.end()) ? 0 : seg[x]; }
    void modify(ll p, ll val) {
        p += N;
        for (seg[p] = max(val, seg[p]); p > 0; p >>= 1) {
            seg[p >> 1] = max(get(p), get(p ^ 1));
        }
    }

    ll query(ll l, ll r) {
        ll res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res = max(res, get(l++));
            if (r & 1)
                res = max(res, get(--r));
        }
        return res;
    }
};

ll N;
array<ll, 3> G[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    gp_hash_table<pair<ll, ll>, ll, phash> prec;
    for (ll i = 0; i < N; i++) {
        ll b, f, d;
        cin >> b >> f >> d;
        prec[{b, f}] += d;
    }
    ll idx = 0;
    for (auto i : prec) {
        G[idx] = {i.first.first, i.first.second, i.second};
        idx++;
    }
    sort(G, G + idx);
    seg dp;
    ll ans = 0;
    for (ll i = 0; i < idx; i++) {
        vector<array<ll, 2>> calcs;
        ll cur = dp.query(0, G[i][1]) + G[i][2];
        calcs.push_back({G[i][1], cur});
        ans = max(cur, ans);
        while (G[i + 1][0] == G[i][0] && i < idx) {
            i++;
            ll cur = dp.query(0, G[i][1]) + G[i][2];
            calcs.push_back({G[i][1], cur});
            ans = max(cur, ans);
        }
        for (auto j : calcs) {
            dp.modify(j[0], j[1]);
        }
    }
    cout << ans << endl;
}