#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

const int MAXN = 1005;
int P, K, N, M;
bool board[MAXN][MAXN];

int color[MAXN][MAXN];
bool isValid(int x, int y) { return (x >= 0 && y >= 0 && x < N && y < M); }
int cnt = 0;
void flood(int x, int y, int clr, bool startType) {
    cnt++;
    if (color[x][y] != -1)
        return;
    if (board[x][y] != startType)
        return;
    color[x][y] = clr;
    vector<array<int, 2>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto i : dirs) {
        if (!isValid(x + i[0], y + i[1]))
            continue;
        flood(x + i[0], y + i[1], clr, startType);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P;
    for (int t = 0; t < P; t++) {
        cin >> K >> N >> M;
        for (int r = 0; r < N; r++) {
            fill(begin(board[r]), end(board[r]), false);
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                char t;
                cin >> t;
                board[i][j] = (t == '0');
            }
        }
        for (int i = 0; i < N; i++) {
            fill(begin(color[i]), end(color[i]), -1);
        }
        // cout << "HUH" << endl;
        int initWhite = 0, initBlack = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // cout << board[i][j];
                if (color[i][j] != -1)
                    continue;
                flood(i, j, i * M + j, board[i][j]);
                if (color[i][j] == i * M + j) {
                    if (board[i][j])
                        initWhite++;
                    else
                        initBlack++;
                }
            }
        }
        cout << "cnt1:" << cnt << endl;
        // cout << "HMM" << endl;
        int mxColors = -1;
        int mxWhite = -1;
        int mxCol = 0;
        for (int c = 0; c < M - 1; c++) {
            set<int> whiteColors;
            set<int> blackColors;
            set<int> destroyedWhite;
            set<int> destroyedBlack;
            for (int r = 0; r < N; r++) {
                if ((c == 0 || color[r][c] != color[r][c - 1]) && (c == M - 1 || color[r][c] != color[r][c + 1])) {
                    if (board[r][c])
                        destroyedWhite.insert(color[r][c]);
                    else
                        destroyedBlack.insert(color[r][c]);
                }
                if (c == 0 || c == M - 1)
                    continue;
                if (color[r][c - 1] == color[r][c] && color[r][c + 1] == color[r][c]) {
                    if (board[r][c])
                        whiteColors.insert(color[r][c]);
                    else
                        blackColors.insert(color[r][c]);
                }
            }
            for (auto i : blackColors) {
                destroyedBlack.erase(i);
            }
            for (auto i : whiteColors) {
                destroyedWhite.erase(i);
            }
            int totalAdded = blackColors.size() + whiteColors.size() - destroyedWhite.size() - destroyedBlack.size();
            if (totalAdded > mxColors ||
                (totalAdded >= mxColors && whiteColors.size() - destroyedWhite.size() > mxWhite)) {
                // cout << "entering if" << endl;
                mxCol = c;
                mxColors = totalAdded;
                mxWhite = whiteColors.size() - destroyedWhite.size();
            }
        }
        for (int r = 0; r < N; r++) {
            board[r][mxCol] = false;
        }
        for (int i = 0; i < N; i++) {
            fill(begin(color[i]), end(color[i]), -1);
        }
        int white = 0, black = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // cout << board[i][j];
                flood(i, j, i * M + j, board[i][j]);
                if (color[i][j] == i * M + j) {
                    if (board[i][j])
                        white++;
                    else
                        black++;
                }
            }
        }
        // cout << "init: " << initWhite << ' ' << initBlack << ' ' << mxColors << ' ' << mxWhite << endl;
        cout << K << ' ' << white << ' ' << black << endl;
        cout << cnt << endl;
    }
}