#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
using namespace std;

int R, C;

int ansHist(vector<int> stacks) {
    stacks.push_back(0);
    stack<array<int, 2>> cur;
    cur.push({-1, -1});
    int ans = 0;
    for (int i = 0; i < stacks.size(); i++) {
        while (stacks[i] <= cur.top()[0]) {
            int h = cur.top()[0];
            cur.pop();
            int l = cur.top()[1];
            ans = max(ans, h * (i - l - 1));
        }
        if (stacks[i] > cur.top()[0])
            cur.push({stacks[i], i});
    }
    return ans;
}
const int MAXN = 1005;
bool grid[MAXN][MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> R >> C;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            char t;
            cin >> t;
            grid[i][j] = (t == '.');
        }
    vector<int> cur;
    for (int i = 0; i < C; i++)
        cur.push_back(grid[0][i]);
    int ans = ansHist(cur);
    for (int r = 1; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c])
                cur[c]++;
            else
                cur[c] = 0;
        }
        ans = max(ans, ansHist(cur));
    }
    cout << ans << endl;
}