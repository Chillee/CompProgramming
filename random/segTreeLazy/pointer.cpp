#include <bits/stdc++.h>

using namespace std;

random_device rd;
mt19937 rng(0);
uniform_int_distribution<int> uni(1, 1e9);
typedef pair<int, int> pii;

const int MAXN = 1e5 + 5;
int N = 8;

int A[MAXN];

struct Tree {
    Tree *pl, *pr;
    int l, r, val, lazy;

    void updateVal() { val = pl->val + pr->val; }
    void propagate() { pl->apply(lazy), pr->apply(lazy), lazy = 0; }
    void apply(int x) { lazy += x, val += (r - l) * x; }

    Tree(int l, int r) : l(l), r(r) {
        if (l + 1 == r) {
            val = A[l];
            return;
        }
        pl = new Tree(l, l + r >> 1);
        pr = new Tree(l + r >> 1, r);
        updateVal();
    }
    void modify(int curl, int curr, int x) {
        if (curl <= l && curr >= r) {
            apply(x);
            return;
        }
        if (curl >= r || curr <= l)
            return;
        propagate();
        pl->modify(curl, curr, x);
        pr->modify(curl, curr, x);
        updateVal();
    }
    int query(int curl, int curr) {
        if (curl <= l && curr >= r)
            return val;
        if (curl >= r || l >= curr)
            return 0;
        propagate();
        return pl->query(curl, curr) + pr->query(curl, curr);
    }
} * seg;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < N; i++) {
        A[i] = i;
    }
    clock_t begin;
    begin = clock();
    seg = new Tree(0, N);
    for (int i = 0; i < 1e7; i++) {
        int a = uni(rng), b = uni(rng);
        if (a > b) {
            swap(a, b);
        }
        seg->modify(a, b, uni(rng));
    }
    for (int i = 0; i < 1e7; i++) {
        int a = uni(rng), b = uni(rng);
        if (a > b) {
            swap(a, b);
        }
        seg->modify(a, b, uni(rng));
    }
    cout << "pointers: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    // seg->modify(0, 4, 1);
    // seg->modify(1, 3, 1);
    // cout << seg->query(0, N) << endl;
    // cout << seg->query(0, 2) << endl;
}
