#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;
int T, N, M;
int grid[MAXN][MAXN];
int prec[4][MAXN][MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N >> M;
        for (int i = 0; i < MAXN; i++) {
            fill(begin(grid[i]), end(grid[i]), 0);
        }
        for (int k = 0; k < 4; k++) {
            for (int i = 0; i < MAXN; i++) {
                fill(begin(prec[k][i]), end(prec[k][i]), 0);
            }
        }
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                cin >> grid[i][j];
            }
        }
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                prec[0][i][j] = max(grid[i][j], max(prec[0][i - 1][j], prec[0][i][j - 1]));
            }
        }
        for (int i = 1; i <= N; i++) {
            for (int j = M; j > 0; j--) {
                prec[1][i][j] = max(grid[i][j], max(prec[1][i - 1][j], prec[1][i][j + 1]));
            }
        }
        for (int i = N; i > 0; i--) {
            for (int j = 1; j <= M; j++) {
                prec[2][i][j] = max(grid[i][j], max(prec[2][i + 1][j], prec[2][i][j - 1]));
            }
        }
        for (int i = N; i > 0; i--) {
            for (int j = M; j > 0; j--) {
                prec[3][i][j] = max(grid[i][j], max(prec[3][i + 1][j], prec[3][i][j + 1]));
            }
        }
        int ans = 1e9 + 5;
        for (int i = 2; i < N; i++) {
            for (int j = 2; j < M; j++) {
                int mx = max(max(prec[0][i - 1][j - 1], prec[1][i - 1][j + 1]), max(prec[2][i + 1][j - 1], prec[3][i + 1][j + 1]));
                int mn = min(min(prec[0][i - 1][j - 1], prec[1][i - 1][j + 1]), min(prec[2][i + 1][j - 1], prec[3][i + 1][j + 1]));
                ans = min(ans, mx - mn);
            }
        }
        cout << ans << endl;
    }
}