#include <bits/stdc++.h>

using namespace std;

int K;
bool grid[8][8];
bool vis[8][8];
bool rev = false;
vector<array<int, 2>> moves = {{2, 1}, {2, -1}, {1, 2}, {1, -2}, {-2, 1}, {-2, -1}, {-1, 2}, {-1, -2}};
bool isValid(int r, int c) { return r >= 0 && c >= 0 && r < 8 && c < 8; }
array<int, 2> prv[8][8];
bool dfs(array<int, 2> cur, array<int, 2> end) {
    queue<array<int, 2>> q;
    q.push(cur);
    while (q.size() > 0) {
        auto cur = q.front();
        // cout << cur[0] << ' ' << cur[1] << endl;
        q.pop();
        if (cur == end)
            return true;
        for (auto m : moves) {
            int nx = cur[0] + m[0], ny = cur[1] + m[1];
            if (!isValid(nx, ny))
                continue;
            if (vis[nx][ny])
                continue;
            vis[nx][ny] = true;
            prv[nx][ny] = cur;
            // cout << "nxt: " << nx << ' ' << ny << endl;
            q.push({nx, ny});
        }
    }
    return false;
}
string convert(array<int, 2> cur) {
    char c = cur[1] + 'a';
    char r = cur[0] + '0' + 1;
    string res;
    res += c;
    res += r;
    return res;
}
vector<string> ans;
void makeMove(array<int, 2> start, array<int, 2> end) {
    ans.push_back(convert(start) + "-" + convert(end));
    assert(grid[start[0]][start[1]]);
    assert(!grid[end[0]][end[1]]);
    swap(grid[start[0]][start[1]], grid[end[0]][end[1]]);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> K;
    for (int i = 0; i < K; i++) {
        char a;
        int r, c;
        cin >> a >> r;
        c = a - 'a';
        r--;
        grid[r][c] = true;
    }
    for (int i = 0; i < K; i++) {
        int er = i / 8, ec = i % 8;
        if (grid[er][ec])
            continue;
        for (int j = K; j < 64; j++) {
            for (int k = 0; k < 8; k++)
                for (int l = 0; l < 8; l++) {
                    vis[k][l] = false;
                    prv[k][l] = {};
                }
            array<int, 2> cur = {j / 8, j % 8};
            if (!grid[cur[0]][cur[1]])
                continue;
            bool res = dfs(cur, {er, ec});
            if (res) {
                array<int, 2> t = {er, ec};
                vector<array<int, 2>> moves;
                while (t != cur) {
                    moves.push_back(t);
                    t = prv[t[0]][t[1]];
                }
                moves.push_back(cur);
                vector<int> found = {0};
                for (int k = 0; k < moves.size(); k++) {
                    if (grid[moves[k][0]][moves[k][1]]) {
                        found.push_back(k);
                    }
                }
                for (int k = 1; k < found.size(); k++) {
                    for (int l = found[k]; l > found[k - 1]; l--)
                        makeMove(moves[l], moves[l - 1]);
                }
                break;
            }
        }
    }
    assert(ans.size() <= 1500);
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i << endl;
    }
}