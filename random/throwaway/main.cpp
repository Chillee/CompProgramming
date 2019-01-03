#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
const int N = 5;
template <typename T> struct Seg {
    const int N;
    vector<T> seg;
    T unit;
    const function<T(T, T)> combine;
    Seg(int n, T arr[], int u, function<T(T, T)> cF) : N(n), unit(u), combine(cF) {
        seg.resize(N * 2);
        for (int i = 0; i < N; i++)
            seg[i + N] = arr[i];
        build();
    }
    void build() {
        for (int i = N - 1; i > 0; --i)
            seg[i] = combine(seg[i << 1], seg[i << 1 | 1]);
    }

    void modify(int p, T value) {
        for (seg[p += N] = value; p >>= 1;)
            seg[p] = combine(seg[p << 1], seg[p << 1 | 1]);
    }

    T query(int l, int r) {
        T resl = unit;
        T resr = unit;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = combine(resl, seg[l++]);
            if (r & 1)
                resr = combine(seg[--r], resr);
        }
        return combine(resl, resr);
    }
};

int A[MAXN];
int mx(int a, int b) { return max(a, b); }
signed main() {
    for (int i = 0; i < 10; i++)
        A[i] = i;
    Seg<int> test(10, A, 0, [](int a, int b) { return a + b; });
    cout << test.query(0, 5) << endl;
}