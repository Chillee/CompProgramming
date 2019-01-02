#include <bits/stdc++.h>

using namespace std;

const int OFFSET = 200 * 2;
const int MAXN = 200 * 5;
int grid[MAXN][MAXN][4];
bool vis[MAXN][MAXN];
bool tryDir(string dir) {
    cout << dir << endl;
    string res;
    cin >> res;
    if (res == "ok") {
        return true;
    } else if (res == "solved") {
        exit(0);
    } else {
        return false;
    }
}
void dfs(int r, int c) {
    vis[r][c] = true;
    vector<string> dirs = {"left", "up", "right", "down"};
    vector<array<int, 2>> diff = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    for (int i = 0; i < 4; i++) {
        if (grid[r][c][i] == 0) {
            if (vis[r + diff[i][0]][c + diff[i][1]])
                continue;
            if (tryDir(dirs[i])) {
                grid[r][c][i] = 1;
                grid[r + diff[i][0]][c + diff[i][1]][(i + 2) % 4] = 1;
                dfs(r + diff[i][0], c + diff[i][1]);
                tryDir(dirs[(i + 2) % 4]);
            }
        }
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    dfs(OFFSET, OFFSET);
    cout << "no way out" << endl;
}