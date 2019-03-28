#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2505;
int N, M;
bool grid[MAXN][MAXN];
int gcolor[MAXN][MAXN];
array<int, 2> prv[MAXN][MAXN], s, e;
bool isValid(int r, int c) { return r >= 0 && c >= 0 && r < N && c < M && !grid[r][c] && gcolor[r][c] == 0; }
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
            prv[r + dr][c + dc] = {r, c};
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
            if (t == 'A')
                s = {i, j};
            else if (t == 'B')
                e = {i, j};
            grid[i][j] = (t == '#');
        }
    color(s[0], s[1], 1);
    if (gcolor[e[0]][e[1]] == 0) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    string path;
    while (e != s) {
        auto nxt = prv[e[0]][e[1]];
        if (nxt[0] > e[0])
            path.append("U");
        else if (nxt[0] < e[0])
            path.append("D");
        else if (nxt[1] > e[1])
            path.append("L");
        else if (nxt[1] < e[1])
            path.append("R");
        e = nxt;
    }
    cout << path.size() << endl;
    reverse(path.begin(), path.end());
    cout << path << endl;
}