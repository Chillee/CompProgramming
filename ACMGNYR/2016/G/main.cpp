#include <bits/stdc++.h>

using namespace std;

const int N = 8;
int grid[N + 5][N + 5];
array<int, 2> exists[N * N + 5];
int rsums[N + 5], csums[N + 5];
int rcnt[N + 5], ccnt[N + 5];
vector<array<int, 2>> dirs = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
bool isValid(int r, int c) { return r >= 0 && c >= 0 && r < N && c < N; }
bool isClose(int r, int c, int nr, int nc) {
    for (auto dir : dirs) {
        if (r + dir[0] == nr && c + dir[1] == nc) {
            return true;
        }
    }
    return false;
}
void add(int r, int c, int val) {
    assert(isValid(r, c));
    grid[r][c] = val;
    rsums[r] += val;
    csums[c] += val;
    rcnt[r]++, ccnt[c]++;
    exists[val] = {r, c};
}
void remove(int r, int c) {
    exists[grid[r][c]] = {-1, -1};
    rsums[r] -= grid[r][c];
    csums[c] -= grid[r][c];
    rcnt[r]--, ccnt[c]--;
    grid[r][c] = -1;
}
void printGrid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << grid[i][j] << ' ';
        cout << endl;
    }
}
bool backtrack(int cur) {
    if (cur == 65) {
        return true;
    }
    if (exists[cur][0] != -1) {
        if (cur != 1 && !isClose(exists[cur][0], exists[cur][1], exists[cur - 1][0], exists[cur - 1][1])) {
            return false;
        }
        return backtrack(cur + 1);
    }
    if (cur == 1) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == -1) {
                    add(i, j, cur);
                    bool res = backtrack(cur + 1);
                    if (res)
                        return true;
                    remove(i, j);
                }
            }
        }
        return false;
    } else {
        int r = exists[cur - 1][0], c = exists[cur - 1][1];
        for (auto dir : dirs) {
            int nr = r + dir[0], nc = c + dir[1];
            if (!isValid(nr, nc))
                continue;
            if (grid[nr][nc] != -1)
                continue;
            add(nr, nc, cur);
            if (rsums[nr] <= 260 && csums[nc] <= 260 && (N - rcnt[nr]) * 64 + rsums[nr] >= 260 && (N - ccnt[nc]) * 64 + csums[nc] >= 260) {
                bool res = backtrack(cur + 1);
                if (res)
                    return res;
            }
            remove(nr, nc);
        }
    }
    return false;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i <= N * N; i++) {
        exists[i] = {-1, -1};
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            if (grid[i][j] > 0) {
                add(i, j, grid[i][j]);
            }
        }
    }
    // printGrid();
    // cout << endl;
    // return 0;
    bool res = backtrack(1);
    // cout << res << endl;
    printGrid();
}