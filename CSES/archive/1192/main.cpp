#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2505;
int N, M;
bool grid[MAXN][MAXN];
int gcolor[MAXN][MAXN];
bool isValid(int r, int c) { return r >= 0 && c >= 0 && r < N && c < M && !grid[r][c]; }
void color(int r, int c, int clr) {
    queue<array<int, 2>> q({{r, c}});
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        r = cur[0], c = cur[1];
        if (gcolor[r][c])
            continue;
        gcolor[r][c] = clr;
        vector<array<int, 2>> dirs = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
        for (auto dir : dirs) {
            int dr = dir[0], dc = dir[1];
            if (!isValid(r + dr, c + dc))
                continue;
            q.push({r + dr, c + dc});
            // color(r + dr, c + dc, clr);
        }
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            char t;
            cin >> t;
            grid[i][j] = (t == '#');
        }
    int ans = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (!grid[i][j] && gcolor[i][j] == 0) {
                ans++;
                color(i, j, i * M + j + 1);
            }
    cout << ans << endl;
}