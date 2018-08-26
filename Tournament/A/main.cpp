#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N;
int A[MAXN];
struct rNode;
rNode *newrNode();
struct rNode {
    rNode *pl, *pr;
    int nl = 0, nr = 0, val = 0;

    void updateVal() { val = min(pl->val, pr->val); }

    void build(int l, int r) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            val = A[nl];
            return;
        }
        (pl = newrNode())->build(nl, nl + nr >> 1);
        (pr = newrNode())->build(nl + nr >> 1, nr);
        updateVal();
    }
    int minquery(int y, int l, int r) {
        if (l >= nr || nl >= r)
            return N;
        if (val >= y)
            return N;
        if (nl + 1 == nr)
            return nl;
        int res = pl->minquery(y, l, r);
        if (res == N) {
            res = pr->minquery(y, l, r);
        }
        return res;
    }
    int maxquery(int y, int l, int r) {
        if (l >= nr || nl >= r)
            return -1;
        if (val >= y) {
            return -1;
        }
        if (nl + 1 == nr)
            return nl;
        int res = pr->maxquery(y, l, r);
        if (res < 0) {
            res = pl->maxquery(y, l, r);
        }
        return res;
    }
};
int bufSize = MAXN * 2;
rNode buf[MAXN * 2];
rNode *newrNode() { return &buf[--bufSize]; }
rNode *seg = newrNode();

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    seg->build(0, N);
    int M;
    cin >> M;
    for (int i = 0; i < M; i++) {
        char t;
        int val;
        cin >> t >> val;
        val--;
        if (t == 'S') {
            cout << seg->maxquery(A[val], 0, val) + 1 << endl;
        } else {
            cout << seg->minquery(A[val], val + 1, N) + 1 << endl;
        }
    }
}