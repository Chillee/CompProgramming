#include <bits/stdc++.h>

using namespace std;
struct Tree {
    Tree *pl, *pr;
    int nl = 0, nr = 0, val = 0;

    void updateVal() { val = max(pl->val, pr->val); }

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
            val += x;
            return;
        }
        pl->modify(p, x);
        pr->modify(p, x);
        updateVal();
    }
    int query(int v) {
        if (val < v)
            return -1;
        if (nl + 1 == nr) {
            if (val >= v)
                return nl;
            else
                return -1;
        }
        int res = pl->query(v);
        if (res == -1)
            res = pr->query(v);
        return res;
    }
};
Tree *tree;
const int MAXN = 2e5 + 5;
int N, M;
int H[MAXN], R[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> H[i];
    for (int i = 0; i < M; i++)
        cin >> R[i];
    tree = new Tree(0, N, H);
    for (int i = 0; i < M; i++) {
        int res = tree->query(R[i]);
        cout << res + 1 << endl;
        if (res != -1)
            tree->modify(res, -R[i]);
    }
}