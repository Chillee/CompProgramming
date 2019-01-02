#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using namespace std;

const int MAXN = 1e6;

int A[MAXN];
struct Node;
Node *newNode();
struct Node {
    Node *pl, *pr;
    int nl = 0, nr = 0, val = 0;

    void updateVal() { val = pl->val + pr->val; }

    void build(int l, int r) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            val = A[nl];
            return;
        }
        (pl = newNode())->build(nl, nl + nr >> 1);
        (pr = newNode())->build(nl + nr >> 1, nr);
        updateVal();
    }
    void modify(int p, int x) {
        if (p < nl || nr <= p) {
            return;
        }
        if (nl + 1 == nr) {
            val = x;
            // A[nl] = x;
            return;
        }
        pl->modify(p, x);
        pr->modify(p, x);
        updateVal();
    }
    int query(int l, int r) {
        if (l <= nl && r >= nr)
            return val;
        if (l >= nr || nl >= r)
            return 0;
        return pl->query(l, r) + pr->query(l, r);
    }
};

int bufSize = MAXN * 2;
Node buf[MAXN * 2];
Node *newNode() { return &buf[--bufSize]; }

struct Seg {
    int seg[2 * MAXN];
    void build() {
        for (int i = MAXN - 1; i > 0; i--)
            seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }

    void modify(int p, int x) {
        for (seg[p += MAXN] = x; p > 0; p >>= 1)
            seg[p >> 1] = seg[p] + seg[p ^ 1];
    }

    int query(int l, int r) {
        int res = 0;
        for (l += MAXN, r += MAXN; l < r; l >>= 1, r >>= 1) {
            // cout << l << ' ' << r << endl;
            if (l & 1)
                res += seg[l++];
            if (r & 1)
                res += seg[--r];
        }
        return res;
    }
};

struct Seg3 {
    int n = MAXN, t[4 * MAXN];
    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            t[v] = t[v * 2] + t[v * 2 + 1];
        }
    }
    int sum(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return sum(v * 2, tl, tm, l, min(r, tm)) + sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    }
};
template <class Node_CItr, class Node_Itr, class Cmp_Fn,
          class _Alloc>
struct my_node_update // custom node update class
{
    typedef long long metadata_type;

    long long query(int x, int y, Node_Itr it = node_begin()) {
        long long ans = 1;
        if (it == node_end())
            return ans;
        // if (it != node_begin()) {
        auto l = it.get_l_child();
        auto r = it.get_r_child();
        if (x <= (**it).first && y >= (**it).first) {
            ans *= it.get_metadata();
            ans *= query(x, y, l);
            ans *= query(x, y, r);
        } else if (x > (**it).first) {
            ans *= query(x, y, r);
        } else if (y < (**it).first) {
            ans *= query(x, y, l);
        }
        // }
        return ans;
    }

    void operator()(Node_Itr it, Node_CItr end_it) // this is called for each node update (and then recursively for subsequently updated nodes)
    {
        auto l = it.get_l_child();
        auto r = it.get_r_child();
        long long left = 1, right = 1;
        if (l != end_it)
            left = l.get_metadata();
        if (r != end_it)
            right = r.get_metadata();
        const_cast<long long &>(it.get_metadata()) = left * right * (**it).second; // product of sub-tree
    }

    virtual Node_CItr node_begin() const = 0;

    virtual Node_CItr node_end() const = 0;
};
typedef tree<long long, long long, less<long long>, rb_tree_tag, my_node_update> Seg4;
Node *seg = newNode();
Seg seg2;
Seg3 seg3;
Seg4 seg4;

const int NUMMOD = 1e5;
const int NUMQUERY = 1e2;
random_device rd;
mt19937 rng(0);
uniform_int_distribution<int> uni(1, MAXN);
signed main() {
    for (int i = 0; i < MAXN; i++) {
        A[i] = rand() % 10;
        seg2.seg[i + MAXN] = A[i];
        seg4.insert({i, A[i]});
    }
    seg->build(0, MAXN);
    seg3.build(A, 1, 0, MAXN - 1);
    seg2.build();
    vector<array<int, 2>> queries;
    for (int i = 0; i < NUMQUERY; i++) {
        int a = uni(rng), b = uni(rng);
        if (a > b)
            swap(a, b);
        queries.push_back({a, b});
    }
    clock_t begin;
    int ans;
    begin = clock();
    ans = 0;
    for (auto i : queries) {
        ans += seg->query(i[0], i[1]);
    }
    cout << "pointer; " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << ans << endl;
    begin = clock();
    ans = 0;
    for (auto i : queries) {
        ans += seg2.query(i[0], i[1]);
    }
    cout << "iterative " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << ans << endl;
    begin = clock();
    ans = 0;
    for (auto i : queries) {
        ans += seg3.sum(1, 0, MAXN, i[0], i[1]);
    }
    cout << "emaxx " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << ans << endl;
    begin = clock();
    ans = 0;
    for (auto i : queries) {
        ans += seg4.query(i[0], i[1], seg4.node_begin());
    }
    cout << "arvind " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << ans << endl;
}