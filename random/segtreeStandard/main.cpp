#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
int seg[2 * MAXN];
int N;

void build() {
    for (int i = N - 1; i >= 0; i--)
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
}

void modify(int p, int val) {
    for (seg[p += N] = val; p > 0; p >>= 1)
        seg[p >> 1] = seg[p] + seg[p ^ 1];
}

int query(int l, int r) {
    int res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += seg[l++];
        if (r & 1)
            res += seg[--r];
    }
    return res;
}

int main() {
    N = 8;
    for (int i = 0; i < N; i++) {
        seg[i + N] = i;
    }
    build();
    assert(query(1, 5) == 10);
    assert(query(0, 8) == 28);
    modify(2, 5);
    cout << query(0, 8) << endl;
    assert(query(0, 8) == 31);

    cout << "Passed test cases" << endl;
    return 0;
}