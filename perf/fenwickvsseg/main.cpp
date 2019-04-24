#include <bits/stdc++.h>

using namespace std;

random_device rd;
mt19937 rng(0);
const int N = 1e6;
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

// int BIT[N];

// int bquery(int idx) {
//     int sum = 0;
//     for (int i = idx; i > 0; i -= i & (-i))
//         sum += BIT[i];
//     return sum;
// }

// void bmodify(int idx, int delta) {
//     for (int i = idx; i <= N; i += (i & -i))
//         BIT[i] += delta;
// }
const int MAXB = 28;
int st[N * 2][MAXB];
int lg[N + 1];
int stquery(int a, int b) {
    int k = 31 - __builtin_clz(b - a);
    return max(st[a][k], st[b - (1 << k)][k]);
}

int A[N];
const int NUMMOD = 1e7;
const int NUMQUERY = 1e7;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    clock_t begin;
    vector<array<int, 2>> queries;
    for (int i = 0; i < NUMQUERY; i++) {
        int a = uni(rng), b = uni(rng);
        if (a > b)
            swap(a, b);
        queries.push_back({a, b});
    }
    for (int i = 0; i < N; i++)
        A[i] = uni(rng);

    for (int i = 0; i < N; i++)
        modify(i, A[i]);
    for (int i = 0; i < N; i++)
        st[i][0] = A[i];
    for (int j = 1; j <= MAXB; j++)
        for (int i = 0; i + (1 << j) <= N; i++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    int ans;
    begin = clock();
    ans = 0;
    for (auto i : queries) {
        ans += stquery(i[0], i[1]);
    }
    cout << "sparse table: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << ans << endl;
    begin = clock();
    ans = 0;
    for (auto i : queries) {
        ans += query(i[0], i[1]);
    }
    cout << "segtree: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << ans << endl;
    // for (int i = 0; i < NUMMOD; i++) {
    //     modify(uni(rng), uni(rng));
    // }
    // begin = clock();
    // ans = 0;
    // // for (int i = 0; i < NUMMOD; i++) {
    // //     bmodify(uni(rng), uni(rng));
    // // }
    // for (int i = 0; i < NUMQUERY; i++) {
    //     int a = uni(rng), b = uni(rng);
    //     if (a > b) {
    //         swap(a, b);
    //     }
    //     ans += bquery(b) - bquery(a);
    // }
    // // cout << ans << endl;
    // cout << "fenwick: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}