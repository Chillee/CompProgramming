#include <bits/stdc++.h>

const int MAXN = 1e3 + 5;
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    int operator()(int x) const { return hash_f(x); }
};

int N, M;
struct seg {
    int seg[2 * MAXN][2 * MAXN];
    void build() {
        for (int c = 2 * M; c >= M; c--)
            for (int r = N - 1; r > 0; r--)
                seg[r][c] = seg[r << 1][c] + seg[r << 1 | 1][c];
        for (int r = 2 * N; r > 0; r--)
            for (int c = M - 1; c > 0; c--)
                seg[r][c] = seg[r][c << 1] + seg[r][c << 1 | 1];
    }
    void modify(int qr, int qc, int val) {
        qr += N, qc += M;
        seg[qr][qc] = val;
        for (int r = qr; r > 0; r >>= 1) {
            for (int c = qc; c > 0; c >>= 1)
                seg[r][c >> 1] = seg[r][c] + seg[r][c ^ 1];
            seg[r >> 1][qc] = seg[r][qc] + seg[r ^ 1][qc];
        }
    }
    int query2(int l, int r, int row) {
        int res = 0;
        for (l += M, r += M; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res += seg[row][l++];
            if (r & 1)
                res += seg[row][--r];
        }
        return res;
    }
    int query(int u, int d, int l, int r) {
        int res = 0;
        for (u += N, d += N; u < d; u >>= 1, d >>= 1) {
            if (u & 1)
                res += query2(l, r, u++);
            if (d & 1)
                res += query2(l, r, --d);
        }
        return res;
    }
};

seg seg1;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            seg1.seg[N + i][M + j] = i * M + j + 1;
        }
    seg1.build();
    // cout << seg1.seg[1][1] << endl;
    cout << seg1.query(0, N, 0, M) << endl;
}