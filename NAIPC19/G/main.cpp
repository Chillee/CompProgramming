#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef long long ll;

struct chash {
    const ll RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    ll operator()(ll x) const { return hash_f(x); }
};

ll N;
gp_hash_table<ll, ll, chash> seg;
const ll OFFSET = 1e9 + 5;

ll get(ll x) { return (seg.find(x) == seg.end()) ? 0 : seg[x]; }
void modify(ll p, ll val) {
    p += OFFSET;
    for (seg[p += 1e10] += val; p > 0; p >>= 1) {
        assert(seg[p] >= 0);
        seg[p >> 1] = get(p) + get(p ^ 1);
    }
}

ll query(ll l, ll r) {
    l += OFFSET, r += OFFSET;
    ll res = 0;
    for (l += 1e10, r += 1e10; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += get(l++);
        if (r & 1)
            res += get(--r);
    }
    return res;
}
struct recSide {
    ll idx;
    ll x;
    array<ll, 2> ys;
    bool isLeft;
};
vector<recSide> recs;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        recs.push_back({i, x1, {y1, y2}, true});
        recs.push_back({i, x2, {y1, y2}, false});
    }
    sort(recs.begin(), recs.end(), [](auto a, auto b) { return a.x < b.x; });
    for (auto i : recs) {
        if (!i.isLeft) {
            modify(i.ys[0], -1), modify(i.ys[1], -1);
            if (query(i.ys[0], i.ys[1] + 1) > 0) {
                cout << 1 << endl;
                return 0;
            }
            continue;
        }
        if (query(i.ys[0], i.ys[1] + 1) > 0) {
            cout << 1 << endl;
            return 0;
        }
        modify(i.ys[0], 1), modify(i.ys[1], 1);
    }
    cout << 0 << endl;
}