#include <bits/stdc++.h>

using namespace std;

int A[100005], N = 8;

struct Tree {
    Tree *pl, *pr;
    int l, r, sum, lazy;

    void update(int x) {
        lazy += x;
        sum += (r - l) * x;
    }
    void propagate() { pl->update(lazy), pr->update(lazy), lazy = 0; }

    Tree(int l, int r) : l(l), r(r) {
        if (l + 1 == r) {
            sum = A[l];
            return;
        }
        pl = new Tree(l, l + r >> 1);
        pr = new Tree(l + r >> 1, r);
        sum = pl->sum + pr->sum;
    }

    void modify(int curl, int curr, int x) {
        if (curl <= l && curr >= r) {
            update(x);
            return;
        }
        if (curl >= r || curr <= l)
            return;
        propagate();
        pl->modify(curl, curr, x);
        pr->modify(curl, curr, x);
        sum = pl->sum + pr->sum;
    }

    int query(int curl, int curr) {
        if (curl <= l && curr >= r)
            return sum;
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
    seg = new Tree(0, N);
    seg->modify(0, 4, 1);
    seg->modify(1, 3, 1);
    cout << seg->query(0, N) << endl;
}