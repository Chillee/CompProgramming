#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using namespace std;

const int MAXN = 1e6;

int A[MAXN];
struct Tree {
    Tree *pl, *pr;
    int nl = 0, nr = 0, val = 0;

    void updateVal() { val = pl->val + pr->val; }

    Tree(int l, int r, int A[]) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            val = A[nl];
            return;
        }
        pl = new Tree(nl, nl + nr >> 1, A);
        pr = new Tree(nl + nr >> 1, nr, A);
        updateVal();
    }
    void modify(int p, int x) {
        if (p < nl || nr <= p) {
            return;
        }
        if (nl + 1 == nr) {
            val = x;
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

template <typename T> struct Seg4 {
    const int N;
    vector<T> seg;
    T unit;
    const function<T(T, T)> combine;
    Seg4(int n, T arr[], int u, function<T(T, T)> cF) : N(n), unit(u), combine(cF), seg(N * 2) {
        for (int i = 0; i < N; i++)
            seg[i + N] = arr[i];
        build();
    }
    void build() {
        for (int i = N - 1; i > 0; --i)
            seg[i] = combine(seg[i << 1], seg[i << 1 | 1]);
    }

    void modify(int p, T value) {
        for (seg[p += N] = value; p >>= 1;)
            seg[p] = combine(seg[p << 1], seg[p << 1 | 1]);
    }

    T query(int l, int r) {
        T resl = unit;
        T resr = unit;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = combine(resl, seg[l++]);
            if (r & 1)
                resr = combine(seg[--r], resr);
        }
        return combine(resl, resr);
    }
};
Tree *seg;
Seg seg2;
Seg3 seg3;
Seg4<int> *seg4;

const int NUMMOD = 1e5;
const int NUMQUERY = 1e6;
random_device rd;
mt19937 rng(0);
uniform_int_distribution<int> uni(1, MAXN);
int mx(int a, int b) { return a + b; }
signed main() {
    for (int i = 0; i < MAXN; i++) {
        A[i] = rand() % 10;
        seg2.seg[i + MAXN] = A[i];
    }
    seg = new Tree(0, MAXN, A);
    seg3.build(A, 1, 0, MAXN - 1);
    seg2.build();
    seg4 = new Seg4<int>(MAXN, A, 0, [](int a, int b) { return a + b; });
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
        ans += seg->query(i[0], i[1]);
    }
    cout << "pointer; " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << ans << endl;
    // begin = clock();
    // ans = 0;
    // for (auto i : queries) {
    //     ans += seg4.query(i[0], i[1], seg4.node_begin());
    // }
    // cout << "arvind " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << ans << endl;
    begin = clock();
    ans = 0;
    for (auto i : queries) {
        ans += seg4->query(i[0], i[1]);
    }
    cout << "abstract iterative; " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << ans << endl;
}