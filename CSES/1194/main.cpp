#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2505;
int N, M;
bool grid[MAXN][MAXN];
vector<array<int, 2>> monsters;
array<int, 2> s;
bool curGrid[MAXN][MAXN];
array<int, 2> prv[MAXN][MAXN];
bool isValid(int r, int c) { return r >= 0 && c >= 0 && r < N && c < M && !curGrid[r][c]; }
array<int, 3> f() {
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            curGrid[i][j] = grid[i][j];
    queue<array<int, 3>> q;
    for (auto i : monsters)
        q.push({i[0], i[1], 0});
    q.push({s[0], s[1], 1});
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        vector<array<int, 2>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for (auto dir : dirs) {
            array<int, 2> npos = {cur[0] + dir[0], cur[1] + dir[1]};
            if (!isValid(npos[0], npos[1]))
                continue;

            if (!curGrid[npos[0]][npos[1]] && cur[2])
                prv[npos[0]][npos[1]] = {cur[0], cur[1]};
            curGrid[npos[0]][npos[1]] = true;
            if (cur[2] == 1 && (npos[0] <= 0 || npos[1] <= 0 || npos[0] >= N - 1 || npos[1] >= M - 1))
                return {true, npos[0], npos[1]};

            q.push({npos[0], npos[1], cur[2]});
        }
    }
    return {0, -1, -1};
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
            if (t == 'M')
                monsters.push_back({i, j});
            if (t == 'A')
                s = {i, j};
        }
    auto res = f();
    if (!res[0]) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    string ans;
    array<int, 2> cur = {res[1], res[2]};
    while (cur != s) {
        auto nxt = prv[cur[0]][cur[1]];
        if (nxt[0] > cur[0])
            ans.push_back('U');
        else if (nxt[0] < cur[0])
            ans.push_back('D');
        else if (nxt[1] > cur[1])
            ans.push_back('L');
        else
            ans.push_back('R');
        cur = nxt;
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    cout << ans << endl;
}