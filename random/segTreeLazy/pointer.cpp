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
    int nl = 0, nr = 0, val = 0;

    void updateVal() { val = pl->val + pr->val; }

    Tree(int l, int r) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            val = A[nl];
            return;
        }
        pl = new Tree(nl, nl + nr >> 1);
        pr = new Tree(nl + nr >> 1, nr);
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
Tree *seg;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < N; i++) {
        A[i] = i;
    }
    clock_t begin;
    begin = clock();
    seg = new Tree(0, N);
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
