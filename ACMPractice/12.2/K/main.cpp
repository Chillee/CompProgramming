#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MAXN = 1e6 + 5;
struct Node;
Node *newNode();
ll A[MAXN * 2];
struct Node {
    Node *pl, *pr, *par;
    ll nl = 0, nr = 0;
    ll rsum = 0;
    ll val = 0;
    ll amtR = 0;

    void updateVal() {
        ll amtAdded = min(pl->rsum, (pr->nr - pr->nl) - pr->val);
        amtR = amtAdded;
        val = pl->val + pr->val + amtAdded;
        rsum = pr->rsum + pl->rsum - amtAdded;
    }

    void build(ll l, ll r) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            val = A[nl];
            return;
        }
        (pl = newNode())->build(nl, nl + nr >> 1);
        (pr = newNode())->build(nl + nr >> 1, nr);
        pl->par = this;
        pr->par = this;
        updateVal();
    }
    void add(ll p, ll x) {
        if (p < nl || nr <= p) {
            return;
        }
        if (nl + 1 == nr) {
            val = 1;
            rsum = x - 1;
            A[nl] = x;
            return;
        }
        pl->add(p, x);
        pr->add(p, x);
        updateVal();
    }
    void erase(ll p) {
        if (p < nl || nr <= p) {
            return;
        }
        if (nl + 1 == nr) {
            val = 0;
            rsum = 0;
            A[nl] = 0;
            return;
        }
        pl->erase(p);
        pr->erase(p);
        updateVal();
    }
    ll query(ll l, ll r, ll csum) {
        if (nl >= l && nr <= r) {
            if (val + csum <= nr - nl) {
                return rsum;
            } else if (val + csum >= nr - nl) {
                return rsum + csum - ((nr - nl) - val);
            }
            assert(false);
        }
        if (l >= nr || nl >= r)
            return csum;

        ll res = pl->query(l, r, csum);
        ll ans = pr->query(l, r, res);
        return ans;
    }
};

ll bufSize = MAXN * 2;
Node buf[MAXN * 2];
Node *newNode() { return &buf[--bufSize]; }
Node *seg = newNode();

ll Q;
unordered_map<ll, ll> maps;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    seg->build(0, MAXN);
    cin >> Q;
    for (ll i = 0; i < Q; i++) {
        char t;
        cin >> t;
        if (t == '?') {
            ll x;
            cin >> x;
            ll res = seg->query(0, x, 0);
            cout << res + A[x] << endl;
        } else if (t == '+') {
            ll x, v;
            cin >> x >> v;
            seg->add(x, v);
            maps[i + 1] = x;
        } else if (t == '-') {
            ll idx;
            cin >> idx;
            seg->erase(maps[idx]);
            maps.erase(idx);
        }
    }
}