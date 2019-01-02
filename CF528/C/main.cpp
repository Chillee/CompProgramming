#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
array<int, 2> pos[3];
int vis[MAXN][MAXN];
array<int, 2> prv[MAXN][MAXN];
bool isValid(array<int, 2> c) { return !(c[0] < 0 || c[0] >= MAXN || c[1] < 0 || c[1] >= MAXN || vis[c[0]][c[1]]); }
set<array<int, 2>> finalAns;
bool first = true;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> pos[0][0] >> pos[0][1];
    cin >> pos[1][0] >> pos[1][1];
    cin >> pos[2][0] >> pos[2][1];
    sort(pos, pos + 3);
    do {
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++) {
                vis[i][j] = 0;
                prv[i][j] = {};
            }
        queue<array<int, 2>> cur;
        cur.push(pos[0]);
        set<array<int, 2>> ans = {pos[0], pos[1]};
        while (!cur.empty()) {
            auto c = cur.front();
            cur.pop();
            vector<array<int, 2>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            bool found = false;
            for (auto dir : dirs) {
                array<int, 2> nxt = {c[0] + dir[0], c[1] + dir[1]};
                if (isValid(nxt)) {
                    prv[nxt[0]][nxt[1]] = c;
                    vis[nxt[0]][nxt[1]] = 1;
                    if (nxt == pos[1]) {
                        found = true;
                        break;
                    }
                    cur.push({c[0] + dir[0], c[1] + dir[1]});
                }
            }
            if (found)
                break;
        }
        auto c = pos[1];
        while (c != pos[0]) {
            ans.insert(c);
            c = prv[c[0]][c[1]];
        }
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                vis[i][j] = 0;
        for (auto i : ans) {
            vis[i[0]][i[1]] = 1;
        }
        cur = {};
        cur.push(pos[2]);
        array<int, 2> end;
        while (!cur.empty()) {
            auto c = cur.front();
            // cout << c[0] << ' ' << c[1] << endl;
            // if (cur.size() > 10)
            //     break;
            cur.pop();
            vector<array<int, 2>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            bool found = false;
            for (auto dir : dirs) {
                array<int, 2> nxt = {c[0] + dir[0], c[1] + dir[1]};
                if (nxt[0] >= 0 && nxt[0] < MAXN && nxt[1] >= 0 && nxt[1] < MAXN && vis[nxt[0]][nxt[1]] == 1) {
                    end = nxt;
                    prv[nxt[0]][nxt[1]] = c;
                    found = true;
                    break;
                }
                if (isValid(nxt)) {
                    vis[nxt[0]][nxt[1]] = 2;
                    prv[nxt[0]][nxt[1]] = c;
                    cur.push({c[0] + dir[0], c[1] + dir[1]});
                }
            }
            if (found)
                break;
        }
        while (end != pos[2]) {
            ans.insert(end);
            end = prv[end[0]][end[1]];
        }
        ans.insert(pos[2]);
        if (ans.size() < finalAns.size() || first) {
            finalAns = ans;
            first = true;
        }
    } while (next_permutation(pos, pos + 3));
    cout << finalAns.size() << endl;
    for (auto i : finalAns) {
        cout << i[0] << ' ' << i[1] << endl;
    }
}