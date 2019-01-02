#include <bits/stdc++.h>

using namespace std;

random_device rd; // only used once to initialise (seed) engine
mt19937 rng(rd());
uniform_int_distribution<int> uni(0, 1e6);

const int MAXN = 1e6 + 5;
int N = 1e6;

int seg[2 * MAXN];
void build() {
    for (int i = N - 1; i > 0; i--)
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
}
void modify(int p, int x) {
    for (seg[p += N] = x; p > 1; p >>= 1)
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
    clock_t begin = clock();
    for (int i = 0; i < 1e5; i++) {
        modify(uni(rng), i);
    }
    for (int i = 0; i < 1e5; i++) {
        int a = uni(rng);
        int b = uni(rng);
        if (a > b) {
            swap(a, b);
        }
        query(a, b);
    }
    cout << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    return 0;
}