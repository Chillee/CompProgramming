#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e5 + 5;
const ll MAXK = 1e8 + 5;
struct Node;
Node *newNode();
struct Node {
    Node *pl, *pr;
    ll nl = 0, nr = 0, val = 0, lazy = 0;

    void updateVal() { val = pl->val + pr->val; }
    void propagate() { pl->apply(lazy), pr->apply(lazy), lazy = 0; }
    void apply(ll x) { lazy += x, val += (nr - nl) * x; }

    void build(ll l, ll r) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            val = 0;
            return;
        }
        (pl = newNode())->build(nl, nl + nr >> 1);
        (pr = newNode())->build(nl + nr >> 1, nr);
        updateVal();
    }
    void modify(ll l, ll r, ll x) {
        if (l <= nl && nr <= r) {
            apply(x);
            return;
        }
        if (l >= nr || nl >= r)
            return;
        propagate();
        pl->modify(l, r, x);
        pr->modify(l, r, x);
        updateVal();
    }
    ll query(ll l, ll r) {
        if (l <= nl && r >= nr)
            return val;
        if (l >= nr || nl >= r)
            return 0;
        propagate();
        return pl->query(l, r) + pr->query(l, r);
    }
};

ll bufSize = MAXN * 2;
Node buf[MAXN * 2];
Node *newNode() { return &buf[--bufSize]; }
Node *seg = newNode();
ll N, M;
set<array<ll, 3>> segs;
void insertSeg(array<ll, 3> seg) {
    if (seg[0] == seg[1])
        return;
    segs.insert(seg);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    seg->build(0, N);
    for (ll i = 0; i < N; i++) {
        segs.insert({i, i + 1, i + 1});
    }
    for (ll i = 0; i < M; i++) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll l, r, x;
            cin >> l >> r >> x;
            l--;
            auto lb = segs.lower_bound({l, -MAXN, -MAXK});
            if ((*lb)[0] != l && lb != segs.begin()) {
                lb--;
            }
            auto ub = segs.lower_bound({r, -MAXN, -MAXK});
            ub--;
            for (auto j = lb; j != ub && j != segs.end();) {
                if (j == lb) {
                    j++;
                } else {
                    seg->modify(j->at(0), j->at(1), abs(x - j->at(2)));
                    j = segs.erase(j);
                }
            }
            if (lb == ub) {
                insertSeg({lb->at(0), l, lb->at(2)});
                seg->modify(l, r, abs(x - lb->at(2)));
                insertSeg({r, lb->at(1), lb->at(2)});
                lb = segs.erase(lb);
            } else {
                insertSeg({lb->at(0), l, lb->at(2)});
                seg->modify(l, lb->at(1), abs(x - lb->at(2)));
                segs.erase(lb);
                insertSeg({r, ub->at(1), ub->at(2)});
                seg->modify(ub->at(0), r, abs(x - ub->at(2)));
                segs.erase(ub);
            }
            segs.insert({l, r, x});
        } else {
            ll l, r;
            cin >> l >> r;
            l--;
            cout << seg->query(l, r) << endl;
        }
    }
}