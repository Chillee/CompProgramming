#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
struct tree {
    const static int MAXN = ::MAXN;
    typedef array<int, 2> T;
    const T unit = {};
    int N;
    T seg[2 * MAXN];
    tree(int n, T arr[]) : N(n) {
        N = n;
        for (int i = 0; i < N; i++)
            seg[i + N] = arr[i];
        build();
    }
    T combine(T a, T b) {
        int val = __gcd(a[0], b[0]);
        if (val == a[0] && val == b[0]) {
            return {val, a[1] + b[1]};
        } else if (val == a[0]) {
            return {val, a[1]};
        } else if (val == b[0]) {
            return {val, b[1]};
        } else {
            return {val, 0};
        }
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
tree *seg;
int N;
array<int, 2> S[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> S[i][0];
        S[i][1] = 1;
    }
    seg = new tree(N, S);
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        cout << r - l - seg->query(l, r)[1] << endl;
    }
}