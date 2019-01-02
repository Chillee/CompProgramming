#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MAXN = 1e6 + 5;

struct Line {
    mutable ll m, b, p;
    bool operator<(const Line &o) const { return m < o.m; }
    bool operator<(const ll &x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> { // upper convex hull.
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = inf;
            return false;
        }
        if (x->m == y->m)
            x->p = x->b > y->b ? inf : -inf;
        else
            x->p = div(y->b - x->b, x->m - y->m);
        return x->p >= y->p;
    }
    void add(ll m, ll b) {
        auto z = insert({m, b, 0}), y = z++, x = y;
        while (isect(y, z))
            z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.m * x + l.b;
    }
};

ll N;
array<ll, 3> rects[MAXN];
LineContainer cht;
ll dp[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> rects[i][0] >> rects[i][1] >> rects[i][2];
    }
    sort(rects, rects + N);
    cht.add(0, 0);
    for (ll i = 0; i < N; i++) {
        dp[i] = cht.query(rects[i][1]);
        dp[i] += rects[i][0] * rects[i][1] - rects[i][2];
        cht.add(-rects[i][0], dp[i]);
    }
    ll ans = -1e18;
    for (ll i = 0; i < N; i++) {
        ans = max(dp[i], ans);
    }
    cout << ans << endl;
}