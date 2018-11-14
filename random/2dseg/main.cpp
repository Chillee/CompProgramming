#include <bits/stdc++.h>

const int MAXN = 1e3 + 5;
using namespace std;

int N, M;
int bit[MAXN][MAXN];
int sum(int x, int y) {
    int ret = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            ret += bit[i][j];
    return ret;
}
void add(int x, int y, int delta) {
    for (int i = x; i < N; i = i | (i + 1))
        for (int j = y; j < M; j = j | (j + 1))
            bit[i][j] += delta;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N = 4, M = 4;
    tree.init(N, M);
    tree.add(0, 0, 4);
    modify(2, 2, 4);
    // add(0, 1, 5);
    // add(1, 3, 5);
    cout << query(0, 0, 4, 4) << endl;
    cout << tree.sum(3, 3) << endl;
}