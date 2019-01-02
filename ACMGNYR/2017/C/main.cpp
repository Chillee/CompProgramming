#include <bits/stdc++.h>

using namespace std;

const int MAXN = 8;
const int MAXR = 105;
int P, K, R, C, numR;
bool existed[MAXN][MAXN];
int grid[MAXN][MAXN];
int color[MAXN][MAXN];
int rNum[MAXR];
vector<array<int, 2>> regions[MAXR];
vector<array<int, 2>> orig[MAXR];

vector<int> xdirs = {1, 0, -1};
vector<int> ydirs = {1, 0, -1};
bool isValid(int r, int c) { return (r >= 0 && c >= 0 && r < R && c < C); }
bool checkSpotValid(int r, int c) {
    for (auto dr : xdirs) {
        for (auto dc : ydirs) {
            if (dr == 0 && dc == 0)
                continue;
            if (!isValid(r + dr, c + dc))
                continue;
            if (grid[r + dr][c + dc] == grid[r][c])
                return false;
        }
    }
    return true;
}
bool backtrack(int curR) {
    if (curR == numR)
        return true;
    // cout << "curR: " << curR << endl;
    do {
        for (auto i : regions[curR]) {
            if (!existed[i[0]][i[1]])
                grid[i[0]][i[1]] = -1;
        }
        bool failed = false;
        for (int i = 0; i < regions[curR].size(); i++) {
            auto cur = regions[curR][i];
            if (grid[cur[0]][cur[1]] != i && existed[cur[0]][cur[1]]) {
                failed = true;
            } else {
                grid[cur[0]][cur[1]] = i;
            }
        }
        for (auto i : regions[curR]) {
            if (!checkSpotValid(i[0], i[1])) {
                failed = true;
                break;
            }
        }
        if (failed)
            continue;
        bool res = backtrack(curR + 1);
        if (res)
            return true;

    } while (next_permutation(regions[curR].begin(), regions[curR].end()));
    regions[curR].clear();
    for (auto i : orig[curR])
        regions[curR].push_back(i);
    for (auto i : regions[curR]) {
        if (!existed[i[0]][i[1]])
            grid[i[0]][i[1]] = -1;
    }
    return false;
}
signed main() {
    for (int p = 0; p < 1; p++) {
        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                grid[i][j] = 0;
                color[i][j] = 0;
                existed[i][j] = false;
            }
        }
        for (int i = 0; i < MAXR; i++) {
            rNum[i] = 0;
            regions[i].clear();
            orig[i].clear();
        }
        cin >> R >> C;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                string t;
                cin >> t;
                if (t[0] != '-') {
                    grid[i][j] = t[0] - '0';
                    grid[i][j]--;
                    existed[i][j] = true;
                } else {
                    grid[i][j] = -1;
                }
            }
        }
        cin >> numR;
        for (int i = 0; i < numR; i++) {
            int n;
            cin >> n;
            rNum[i] = n;
            for (int j = 0; j < n; j++) {
                int r, c;
                scanf(" (%d,%d)", &r, &c);
                r--, c--;
                color[r][c] = i;
                regions[i].push_back({r, c});
                orig[i].push_back({r, c});
            }
            sort(regions[i].begin(), regions[i].end());
            sort(orig[i].begin(), orig[i].end());
        }
        bool res = backtrack(0);
        // cout << res << endl;
        for (int i = 0; i < R; i++) {
            cout << grid[i][0] + 1;
            for (int j = 1; j < C; j++) {
                cout << ' ' << grid[i][j] + 1;
            }
            cout << endl;
        }
    }
}