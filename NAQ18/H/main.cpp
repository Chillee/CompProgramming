#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long double ll;

const ll is_query = -(1LL << 60);
struct Line {
    ll m, b;
    mutable function<const Line *()> succ;
    bool operator<(const Line &rhs) const {
        if (rhs.b != is_query)
            return m < rhs.m;
        const Line *s = succ();
        if (!s)
            return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end())
                return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end())
            return y->m == x->m && y->b <= x->b;
        return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
    }
    void insert_line(ll m, ll b) {
        auto y = insert({m, b});
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) {
            erase(y);
            return;
        }
        while (next(y) != end() && bad(next(y)))
            erase(next(y));
        while (y != begin() && bad(prev(y)))
            erase(prev(y));
    }
    ll eval(ll x) {
        auto l = *lower_bound({x, is_query});
        return l.m * x + l.b;
    }
};
HullDynamic chull;
long long N, P, C;
long double binSearch(long double l, long double r, int iter) {
    long double mid = (l + r) / 2;
    if (iter == 500)
        return mid;

    if (abs(chull.eval(mid)) > N) {
        return binSearch(l, mid, iter + 1);
    } else {
        return binSearch(mid, r, iter + 1);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> P >> C;
    chull.insert_line(-1, 0);
    for (int i = 0; i < P; i++) {
        long double t, x, y;
        cin >> t >> x >> y;
        long double slope = (y / x);
        long double yint = -chull.eval(t) - slope * t + C;
        chull.insert_line(-slope, -yint);
    }
    cout << fixed << setprecision(20) << binSearch(0, 1e15, 0) << endl;
}