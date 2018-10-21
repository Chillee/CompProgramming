#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 505;
int N, M, Q;
bool board[MAXN][MAXN];
int color[MAXN][MAXN];
bool isValid(int r, int c) { return r >= 0 && c >= 0 && r < N && c < M; }
void flood(int r, int c, int clr) {
    if (color[r][c] != -1)
        return;
    vector<array<int, 2>> dirs = { {} }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> board[i][j];
        }
    }
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int rs, cs, re, ce;
        cin >> cs >> rs >> ce >> re;
        cs--, rs--, re--, ce--;
    }
}