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
    int nl = 0, nr = 0, val = 0, lazy = 0;

    void updateVal() { val = pl->val + pr->val; }
    void propagate() { pl->apply(lazy), pr->apply(lazy), lazy = 0; }
    void apply(int x) { lazy += x, val += (nr - nl) * x; }

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
    void modify(int l, int r, int x) {
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
    int query(int l, int r) {
        if (l <= nl && r >= nr)
            return val;
        if (l >= nr || nl >= r)
            return 0;
        propagate();
        return pl->query(l, r) + pr->query(l, r);
    }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < N; i++) {
        A[i] = i;
    }
    clock_t begin;
    begin = clock();
    Tree *seg = new Tree(0, N, A);
    for (int i = 0; i < 1e5; i++) {
        int a = uni(rng), b = uni(rng);
        if (a > b) {
            swap(a, b);
        }
        seg->modify(a, b, uni(rng));
    }
    for (int i = 0; i < 1e5; i++) {
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
