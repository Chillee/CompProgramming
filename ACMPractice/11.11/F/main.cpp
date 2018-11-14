#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
typedef long long ll;
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

struct recSeg {
    ll x, y1, y2;
    bool isLeft;
    bool operator<(recSeg b) { return make_tuple(x, y1, y2, isLeft) < make_tuple(b.x, b.y1, b.y2, b.isLeft); }
};
ll N;
vector<recSeg> segs;
gp_hash_table<ll, ll, chash> comp;
vector<ll> vals;

struct Node;
Node *newNode();
struct Node {
    Node *pl, *pr;
    ll nl = 0, nr = 0, val = 0;
    bool parity = false;
    bool lazy = false;
    bool tag = false;

    void updateVal() {
        val = pl->val + pr->val;
        tag = false;
        parity = false;
    }
    void propagate() { pl->apply(lazy), pr->apply(lazy), lazy = 0; }
    void apply(bool x) {
        lazy ^= x;
        if (x)
            val = (vals[nr] - vals[nl]) - val;
    }

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
            // cout << vals[nr] << ' ' << vals[nl] << ' ' << vals[nr] - vals[nl] << endl;
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
const ll MAXN = 2e5 + 5;
ll bufSize = MAXN * 2;
Node buf[MAXN * 2];
Node *newNode() { return &buf[--bufSize]; }
Node *seg = newNode();
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // vals = {0, 10, 20, 30, 40, 50, 60, 70, 80};
    // seg->build(0, 8);
    // seg->modify(0, 8, 1);
    // seg->modify(1, 7, 1);
    // seg->modify(2, 6, 1);
    // seg->modify(3, 5, 1);
    // cout << seg->query(0, 8) << endl;
    cin >> N;
    set<ll> cvals;
    for (ll i = 0; i < N; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);
        segs.push_back({x1, y1, y2, true});
        segs.push_back({x2, y1, y2, false});
        cvals.insert(y1);
        cvals.insert(y2);
    }
    for (auto i : cvals) {
        vals.push_back(i);
    }
    for (ll i = 0; i < vals.size(); i++) {
        comp[vals[i]] = i;
    }
    for (auto &i : segs) {
        i.y1 = comp[i.y1];
        i.y2 = comp[i.y2];
    }
    sort(segs.begin(), segs.end());
    seg->build(0, vals.size() - 1);
    // seg->modify(0, 4, 1);
    // cout << segs[0].x << ' ' << vals[segs[0].y1] << ' ' << vals[segs[0].y2] << endl;
    seg->modify(segs[0].y1, segs[0].y2, 1);
    // cout << seg->query(0, 3) << endl;
    ll ans = 0;
    for (ll i = 1; i < segs.size(); i++) {
        // cout << segs[i].x << ' ' << vals[segs[i].y1] << ' ' << vals[segs[i].y2] << endl;
        // cout << seg->query(0, vals.size() - 1) << endl;
        ans += seg->query(0, vals.size() - 1) * (segs[i].x - segs[i - 1].x);
        seg->modify(segs[i].y1, segs[i].y2, 1);
    }
    cout << ans << endl;
}