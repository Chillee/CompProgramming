#include <bits/stdc++.h>

using namespace std;

int N, M;
string S;
struct Tree {
    Tree *pl, *pr;
    int nl = 0, nr = 0;
    array<int, 2> total;
    array<int, 2> prf, suff, in;

    void updateVal() {
        if (pl->total[0] && pr->total[0] && pl->total[1] == pr->total[1]) {
            total = {true, pl->total[1]};
        } else
            total = {false, -1};
        if (pl->total[0] && pr->prf[0] == pl->total[1]) {
            prf = {pl->total[1], (pl->nr - pl->nl) + pr->prf[1]};
        } else
            prf = pl->prf;
        if (pr->total[0] && pl->suff[0] == pr->total[1]) {
            suff = {pr->total[1], (pr->nr - pr->nl) + pl->suff[1]};
        } else
            suff = pr->suff;
        auto cmp = [](array<int, 2> a, array<int, 2> b) { return make_pair(a[1], a[0]) < make_pair(b[1], b[0]); };
        in = max(pl->in, pr->in, cmp);
        if (pl->suff[0] == pr->prf[0])
            in = max(in, {pl->suff[0], pl->suff[1] + pr->prf[1]}, cmp);
    }

    Tree(int l, int r, int A[]) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            prf = suff = in = {A[nl], 1};
            total = {true, A[nl]};
            return;
        }
        pl = new Tree(nl, nl + nr >> 1, A);
        pr = new Tree(nl + nr >> 1, nr, A);
        updateVal();
    }
    void modify(int p) {
        if (p < nl || nr <= p) {
            return;
        }
        if (nl + 1 == nr) {
            int x = !prf[0];
            prf = suff = in = {x, 1};
            total = {true, x};
            return;
        }
        pl->modify(p);
        pr->modify(p);
        updateVal();
    }
    int query() {
        if (total[0])
            return (nr - nl);
        return max(max(prf[1], suff[1]), in[1]);
    }
};
vector<int> A;
Tree *seg;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    N = S.size();
    for (auto i : S)
        A.push_back(i == '1');
    seg = new Tree(0, N, A.data());
    cin >> M;
    for (int i = 0; i < M; i++) {
        int x;
        cin >> x;
        x--;
        seg->modify(x);
        cout << seg->query() << ' ';
    }
    cout << endl;
}