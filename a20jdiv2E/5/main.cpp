#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MAXBITS = 22;

ll N, M;
ll A[MAXN];

struct Tree;
Tree *newNode();
struct Tree {
    Tree *pl, *pr;
    ll l, r, val[MAXBITS], lazy[MAXBITS];

    void updateVal() {
        for (ll i = 0; i < MAXBITS; i++) {
            val[i] = pl->val[i] + pr->val[i];
        }
    }
    void propagate() { pl->apply(lazy), pr->apply(lazy), fill(lazy, lazy + MAXBITS, 0); }
    void apply(ll x[MAXBITS]) {
        for (ll i = 0; i < MAXBITS; i++) {
            if (x[i] == 0)
                continue;
            lazy[i] ^= x[i], val[i] = (r - l) - val[i];
        }
    }

    void build(ll curl, ll curr) {
        l = curl, r = curr;
        if (l + 1 == r) {
            for (ll i = 0; i < MAXBITS; i++) {
                val[i] = (A[l] & (1 << i)) ? 1 : 0;
            }
            return;
        }
        (pl = newNode())->build(l, l + r >> 1);
        (pr = newNode())->build(l + r >> 1, r);
        updateVal();
    }
    void modify(ll curl, ll curr, ll x[MAXBITS]) {
        if (curl <= l && r <= curr) {
            apply(x);
            return;
        }
        if (curr <= l || r <= curl)
            return;
        propagate();
        pl->modify(curl, curr, x);
        pr->modify(curl, curr, x);
        updateVal();
    }
    ll query(ll curl, ll curr) {
        ll ans = 0;
        if (curl <= l && r <= curr) {
            for (ll i = 0; i < MAXBITS; i++) {
                ans += val[i] * (1 << i);
            }
            return ans;
        }
        if (curr <= l || r <= curl)
            return 0;
        propagate();
        return pl->query(curl, curr) + pr->query(curl, curr);
    }
};
ll bufSize = MAXN * 2;
Tree buf[MAXN * 2];
Tree *newNode() { return &buf[--bufSize]; }
Tree *seg;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    seg = newNode();
    seg->build(0, N);
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
            cout << seg->query(a, b + 1) << endl;
        } else {
            ll a, b, x;
            cin >> a >> b >> x;
            a--, b--;
            ll modify[MAXBITS];
            for (ll bit = 0; bit < MAXBITS; bit++) {
                modify[bit] = (x & (1 << bit)) ? 1 : 0;
            }
            seg->modify(a, b + 1, modify);
        }
    }
}