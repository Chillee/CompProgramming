#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
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

const ll is_query = -(1LL << 60);
struct Line2 {
    ll m, b;
    mutable function<const Line2 *()> succ;
    bool operator<(const Line2 &rhs) const {
        if (rhs.b != is_query)
            return m < rhs.m;
        const Line2 *s = succ();
        if (!s)
            return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line2> { // will maintain upper hull for maximum
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
typedef long double ld;
const ld inf = 1e18;
struct chtDynamic {
    struct line {
        ll m, b;
        ld x;
        ll val;
        bool isQuery;
        line(ll _m = 0, ll _b = 0) : m(_m), b(_b), val(0), x(-inf), isQuery(false) {}

        ll eval(ll x) const { return m * x + b; }
        bool parallel(const line &l) const { return m == l.m; }
        ld intersect(const line &l) const { return parallel(l) ? inf : 1.0 * (l.b - b) / (m - l.m); }
        bool operator<(const line &l) const {
            if (l.isQuery)
                return x < l.val;
            else
                return m < l.m;
        }
    };

    set<line> hull;
    typedef set<line>::iterator iter;

    bool cPrev(iter it) { return it != hull.begin(); }
    bool cNext(iter it) { return it != hull.end() && next(it) != hull.end(); }

    bool bad(const line &l1, const line &l2, const line &l3) { return l1.intersect(l3) <= l1.intersect(l2); }
    bool bad(iter it) { return cPrev(it) && cNext(it) && bad(*prev(it), *it, *next(it)); }

    iter update(iter it) {
        if (!cPrev(it))
            return it;
        ld x = it->intersect(*prev(it));
        line tmp(*it);
        tmp.x = x;
        it = hull.erase(it);
        return hull.insert(it, tmp);
    }

    void addLine(ll m, ll b) {
        line l(m, b);
        iter it = hull.lower_bound(l);
        if (it != hull.end() && l.parallel(*it)) {
            if (it->b < b)
                it = hull.erase(it);
            else
                return;
        }

        it = hull.insert(it, l);
        if (bad(it))
            return (void)hull.erase(it);

        while (cPrev(it) && bad(prev(it)))
            hull.erase(prev(it));
        while (cNext(it) && bad(next(it)))
            hull.erase(next(it));

        it = update(it);
        if (cPrev(it))
            update(prev(it));
        if (cNext(it))
            update(next(it));
    }

    ll query(ll x) const {
        if (hull.empty())
            return -inf;
        line q;
        q.val = x, q.isQuery = 1;
        iter it = --hull.lower_bound(q);
        return it->eval(x);
    }
} ds;
LineContainer cht1;
HullDynamic cht2;
chtDynamic cht3;
const int NUM_INSERTS = 1e7;
const int NUM_QUERIES = 1e7;
vector<int> res1, res2, res3;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<array<int, 2>> lines;
    vector<int> queries;
    for (int i = 0; i < NUM_INSERTS; i++)
        lines.push_back({rand(), rand()});
    for (int i = 0; i < NUM_QUERIES; i++)
        queries.push_back(rand());

    clock_t begin;
    begin = clock();
    for (auto i : lines)
        cht1.add(i[0], i[1]);
    for (auto i : queries)
        res1.push_back(cht1.query(i));

    cout << "LineContainer: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    begin = clock();
    for (auto i : lines)
        cht2.insert_line(i[0], i[1]);
    for (auto i : queries)
        res2.push_back(cht2.eval(i));

    cout << "HullDynamic:   " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    begin = clock();
    for (auto i : lines)
        cht3.addLine(i[0], i[1]);
    for (auto i : queries)
        res3.push_back(cht3.query(i));

    cout << "chtDynamic:    " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;

    // for (int i = 0; i < res1.size(); i++)
    //     assert(res1[i] == res2[i]);
}