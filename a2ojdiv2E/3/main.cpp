#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1e6 + 5;
typedef struct info {
    int paired;
    int left;
    int right;
} info;

int N;
string S;

info combine(info l, info r) {
    info res;
    res.left = l.left + r.left;
    res.right = l.right + r.right;
    res.paired = l.paired + r.paired + min(l.left - l.paired, r.right - r.paired);
    return res;
}

info seg[2 * MAXN];
void build() {
    for (int i = N - 1; i > 0; --i)
        seg[i] = combine(seg[i << 1], seg[i << 1 | 1]);
}

void modify(int p, info value) {
    for (seg[p += N] = value; p >>= 1;)
        seg[p] = combine(seg[p << 1], seg[p << 1 | 1]);
}

info query(int l, int r) {
    info resl = {};
    info resr = {};
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            resl = combine(resl, seg[l++]);
        if (r & 1)
            resr = combine(seg[--r], resr);
    }
    return combine(resl, resr);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    N = S.size();
    for (int i = N; i < 2 * N; i++) {
        seg[i] = {};
        seg[i].left = 0;
        seg[i].right = 0;
        seg[i].paired = 0;
        if (S[i - N] == '(') {
            seg[i].left = 1;
        } else if (S[i - N] == ')') {
            seg[i].right = 1;
        }
    }
    build();
    int M;
    cin >> M;
    for (int i = 0; i < M; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        cout << query(l, r).paired * 2 << endl;
    }
}