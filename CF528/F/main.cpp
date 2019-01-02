#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int bSize;
int N, Q;
string S;
array<int, 3> cnt[MAXN];

struct seg {
    int seg[2 * MAXN];
    void build() {
        for (int i = N - 1; i >= 0; i--)
            seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }

    void modify(int p, int val) {
        for (seg[p += N] = val; p > 0; p >>= 1)
            seg[p >> 1] = seg[p] + seg[p ^ 1];
    }

    int query(int l, int r) {
        if (l == r)
            return 1;
        int res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res += seg[l++];
            if (r & 1)
                res += seg[--r];
        }
        return res;
    }
};
seg cnts[3];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q;
    bSize = sqrt(N);
    cin >> S;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == 'R')
            cnt[i][0] = 1;
        else if (S[i] == 'P')
            cnt[i][1] = 1;
        else
            cnt[i][2] = 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++)
            cnts[j].seg[i + N] = cnt[i][j];
    }
    int cur = 0;
    for (int i = 1; i < N; i++) {
        if (S[i] == 'R') {
            cur += (cnts[2].query(i, N) > 0 && cnts[2].query(0, i) > 0);
        } else if (S[i] == 'P') {
            cur += (cnts[0].query(i, N) > 0 && cnts[0].query(0, i) > 0);
        } else {
            cur += (cnts[1].query(i, N) > 0 && cnts[1].query(0, i) > 0);
        }
    }
    for (int i = 0; i < Q; i++) {
        int t;
        char c;
        cin >> t >> c;
    }
}