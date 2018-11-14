#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

int N, M, D;
vector<vector<bool>> vis, vis2;
bool isValid(int r, int c) { return r >= 0 && c >= 0 && r < N && c < M; }
void bfs(vector<array<int, 2>> pos) {
    queue<array<int, 3>> cur;
    for (auto i : pos) {
        cur.push({i[0], i[1], 0});
    }
    while (!cur.empty()) {
        auto cp = cur.front();
        cur.pop();
        if (!isValid(cp[0], cp[1]) || vis[cp[0]][cp[1]] || cp[2] > D)
            continue;
        vis[cp[0]][cp[1]] = true;
        vector<array<int, 2>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto dir : dirs) {
            cur.push({cp[0] + dir[0], cp[1] + dir[1], cp[2] + 1});
        }
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> D;
    vis.resize(N + 5);
    vis2.resize(N + 5);
    for (auto &i : vis) {
        i.resize(M + 5);
    }
    for (auto &i : vis2) {
        i.resize(M + 5);
    }

    int sx, sy;
    int fx, fy;
    vector<array<int, 2>> pos;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char t;
            cin >> t;
            if (t == 'S') {
                sx = i, sy = j;
            } else if (t == 'F') {
                fx = i, fy = j;
            } else if (t == 'M') {
                pos.push_back({i, j});
            }
        }
    }
    bfs(pos);
    queue<array<int, 3>> cur;
    cur.push({sx, sy, 0});
    while (!cur.empty()) {
        auto cp = cur.front();
        cur.pop();
        if (!isValid(cp[0], cp[1]) || vis[cp[0]][cp[1]])
            continue;
        if (cp[0] == fx && cp[1] == fy) {
            cout << cp[2] << endl;
            return 0;
        }
        vis[cp[0]][cp[1]] = true;
        vector<array<int, 2>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto dir : dirs) {
            cur.push({cp[0] + dir[0], cp[1] + dir[1], cp[2] + 1});
        }
    }
    cout << -1 << endl;
}