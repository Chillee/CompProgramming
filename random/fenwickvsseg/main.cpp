#include <bits/stdc++.h>

using namespace std;

random_device rd;
mt19937 rng(0);
const int N = 1e8;
uniform_int_distribution<int> uni(1, N);
int seg[2 * N];

void modify(int p, int val) {
    for (seg[p += N] = val; p > 0; p >>= 1)
        seg[p >> 1] = max(seg[p], seg[p ^ 1]);
}

int query(int l, int r) {
    int res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res = max(res, seg[l++]);
        if (r & 1)
            res = max(seg[--r], res);
    }
    return res;
}

int BIT[N];

int bquery(int idx) {
    int sum = 0;
    for (int i = idx; i > 0; i -= i & (-i))
        sum += BIT[i];
    return sum;
}

void bmodify(int idx, int delta) {
    for (int i = idx; i <= N; i += (i & -i))
        BIT[i] += delta;
}
const int NUMMOD = 1e8;
const int NUMQUERY = 1e8;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    clock_t begin;
    begin = clock();
    for (int i = 0; i < NUMMOD; i++) {
        modify(uni(rng), uni(rng));
    }
    for (int i = 0; i < NUMQUERY; i++) {
        int a = uni(rng), b = uni(rng);
        if (a > b) {
            swap(a, b);
        }
        query(a, b);
    }
    cout << "segtree: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    begin = clock();
    for (int i = 0; i < NUMMOD; i++) {
        bmodify(uni(rng), uni(rng));
    }
    for (int i = 0; i < NUMQUERY; i++) {
        int a = uni(rng), b = uni(rng);
        if (a > b) {
            swap(a, b);
        }
        bquery(b) - bquery(a);
    }
    cout << "fenwick: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}