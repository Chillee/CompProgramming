#include <bits/stdc++.h>

using namespace std;

int N = 8;
int H = sizeof(int) * 8 - __builtin_clz(N);
int seg[100005];
int lazy[100005];

void apply(int p, int value, int k) {
    seg[p] += value * k;
    if (p < N) {
        lazy[p] += value;
    }
}

void propDown(int p) {
    int k = 1 << (H - 1);
    for (int s = H; s > 0; s--, k >>= 1) {
        int i = p >> s;
        if (lazy[i] != 0) {
            apply(i << 1, lazy[i], k);
            apply(i << 1 | 1, lazy[i], k);
            lazy[i] = 0;
        }
    }
}

void propUp(int p) {
    int k = 2;
    while (p > 1) {
        p >>= 1;
        seg[p] = seg[p << 1] + seg[p << 1 | 1] + lazy[p] * k;
        k <<= 1;
    }
}

void inc(int l, int r, int val) {
    l += N, r += N;
    int l0 = l, r0 = r, k = 1;
    for (; l < r; l >>= 1, r >>= 1, k <<= 1) {
        if (l & 1)
            apply(l++, val, k);
        if (r & 1)
            apply(--r, val, k);
    }
    propUp(l0);
    propUp(r0 - 1);
}

int query(int l, int r) {
    l += N, r += N;
    propDown(l);
    propDown(r - 1);
    int res = 0;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            res += seg[l++];
        }
        if (r & 1)
            res += seg[--r];
    }
    return res;
}

int main() {
    for (int i = 0; i < N; i++) {
        seg[i + N] = i;
    }
    for (int i = 0; i < N; i++) {
        propUp(i + N);
    }
    inc(0, 4, 1);
    inc(1, 3, 1);
    for (int i = 1; i < N; i++) {
        propDown(i + N);
    }
    for (int i = 0; i < 2 * N; i++) {
        cout << "(" << seg[i] << ", " << lazy[i] << ") ";
    }
    cout << endl;
    cout << query(0, N) << endl;
}