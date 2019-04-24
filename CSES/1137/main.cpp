#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
ll N, Q;
ll val[MAXN];
vector<ll> adj[MAXN];
ll tim = 0;
ll begT[MAXN], endT[MAXN];
ll valT[MAXN];
template <typename T> struct Seg {
    const ll N;
    vector<T> seg;
    T unit;
    const function<T(T, T)> combine;
    Seg(ll n, T arr[], T u, function<T(T, T)> cF) : N(n), unit(u), combine(cF), seg(N * 2) {
        for (ll i = 0; i < N; i++)
            seg[i + N] = arr[i];
        build();
    }
    void build() {
        for (ll i = N - 1; i > 0; --i)
            seg[i] = combine(seg[i << 1], seg[i << 1 | 1]);
    }

    void modify(ll p, T value) {
        for (seg[p += N] = value; p > 0; p >>= 1)
            seg[p >> 1] = combine(seg[p], seg[p ^ 1]);
    }

    T query(ll l, ll r) {
        T resl = unit;
        T resr = unit;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = combine(resl, seg[l++]);
            if (r & 1)
                resr = combine(seg[--r], resr);
        }
        return combine(resl, resr);
    }
};
void dfs(ll cur, ll p = -1) {
    begT[cur] = tim++;
    valT[begT[cur]] = val[cur];
    for (auto i : adj[cur]) {
        if (i != p)
            dfs(i, cur);
    }
    endT[cur] = tim;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q;
    for (ll i = 0; i < N; i++)
        cin >> val[i];
    for (ll i = 0; i < N - 1; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0);
    Seg<ll> *seg = new Seg<ll>(N, valT, 0, [](ll a, ll b) { return a + b; });
    for (ll i = 0; i < Q; i++) {
        ll t;
        cin >> t;
        if (t == 2) {
            ll v;
            cin >> v;
            v--;
            cout << seg->query(begT[v], endT[v]) << endl;
        } else {
            ll v, x;
            cin >> v >> x;
            v--;
            seg->modify(begT[v], x);
        }
    }
}