#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;

bool Q;
struct Line {
    mutable ll m, b, p;
    bool operator<(const Line &o) const { return Q ? p < o.p : m < o.m; }
};

struct LineContainer : multiset<Line> { // Maintains upper hull.
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
        Q = 1;
        auto l = *lower_bound({0, 0, x});
        Q = 0;
        return l.m * x + l.b;
    }
};
LineContainer chull;
long long N, P, C;
long double binSearch(long double l, long double r, int iter) {
    long double mid = (l + r) / 2;
    if (iter == 500)
        return mid;

    if (abs(chull.query(mid)) > N) {
        return binSearch(l, mid, iter + 1);
    } else {
        return binSearch(mid, r, iter + 1);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> P >> C;
    chull.add(-1, 0);
    for (int i = 0; i < P; i++) {
        long double t, x, y;
        cin >> t >> x >> y;
        long double slope = (y / x);
        long double yint = -chull.query(t) - slope * t + C;
        chull.add(-slope, -yint);
    }
    cout << fixed << setprecision(20) << binSearch(0, 1e15, 0) << endl;
}