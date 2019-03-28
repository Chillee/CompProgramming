#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
int R, C;
bool sgrid[MAXN][MAXN], egrid[MAXN][MAXN];
int rDown[MAXN], cDown[MAXN];
void fail() {
    cout << "0" << endl;
    exit(0);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> R >> C;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            char t;
            cin >> t;
            sgrid[i][j] = (t == 'X');
        }
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            char t;
            cin >> t;
            egrid[i][j] = (t == 'X');
        }
    int totCount = 0;
    bool allX = true;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            rDown[r] += egrid[r][c];
            cDown[c] += egrid[r][c];
            totCount += !egrid[r][c];
            allX = allX && sgrid[r][c];
        }
    }
    if (allX && totCount != 0)
        fail();
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (rDown[r] > 1 && egrid[r][c] != sgrid[r][c])
                fail();
            if (cDown[c] > 1 && egrid[r][c] != sgrid[r][c])
                fail();
        }
    }
    cout << "1" << endl;
}
