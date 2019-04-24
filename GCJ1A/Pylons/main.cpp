#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

int T, R, C;
const int MAXN = 20;
int grid[MAXN][MAXN];
bool solve(int r, int c, int step) {
    bool done = true;
    // for (int i = 0; i < R; i++) {
    //     for (int j = 0; j < C; j++) {
    //         cout << grid[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << r << ' ' << c << endl;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            // cout << i << ' ' << j << endl;
            if (grid[i][j] != 0)
                continue;
            // cout << i << ' ' << j << endl;
            if (i != r && j != c && i - j != r - c && i + j != r + j) {
                // cout << "nxt: " << i << ' ' << j << endl;
                grid[i][j] = step;
                done = solve(i, j, step + 1);
                if (done)
                    return true;
                grid[i][j] = 0;
            }
        }
    }
    return false;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> R >> C;
    bool done = solve(1000, 100, 1);
    cout << done << endl;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
}