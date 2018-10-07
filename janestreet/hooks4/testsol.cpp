#include <bits/stdc++.h>

using namespace std;

const int MAXN = 9;
int grid[MAXN][MAXN];

bool vis[MAXN][MAXN];

int dfs2(int x, int y) {
    if (x < 0 || y < 0 || x >= MAXN || y >= MAXN)
        return 0;
    if (vis[x][y] || grid[x][y] != 0)
        return 0;
    vis[x][y] = true;
    vector<int> dir = {1, 0, -1};
    int sz = 1;
    for (auto dx : dir) {
        for (auto dy : dir) {
            if (dx != 0 && dy != 0)
                continue;
            sz += dfs2(x + dx, y + dy);
        }
    }
    return sz;
}
int getAns() {
    int ans = 1;
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            vis[i][j] = false;
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            int res = dfs2(i, j);
            if (res != 0)
                ans *= res;
        }
    }
    return ans;
}
void dfs(int x, int y) {
    if (x < 0 || y < 0 || x >= MAXN || y >= MAXN)
        return;
    if (vis[x][y] || grid[x][y] == 0)
        return;
    vis[x][y] = true;
    vector<int> dir = {1, 0, -1};
    for (auto dx : dir) {
        for (auto dy : dir) {
            if (dx != 0 && dy != 0)
                continue;
            dfs(x + dx, y + dy);
        }
    }
}
bool isConnected() {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++)
            vis[i][j] = false;
    }
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            if (grid[i][j] > 0) {
                dfs(i, j);
                for (int x = 0; x < MAXN; x++) {
                    for (int y = 0; y < MAXN; y++) {
                        if (!(vis[x][y] || grid[x][y] == 0))
                            return false;
                    }
                }
                return true;
            }
        }
    }
    return true;
}

int getProd(vector<int> &vals) {
    int ans = 0;
    bool inSeq = false;
    int curProd = 1;
    for (auto i : vals) {
        if (i == -1)
            i = 0;
        if (inSeq && i != 0)
            curProd *= i;
        else if (inSeq && i == 0) {
            ans += curProd;
            curProd = 1;
            inSeq = false;
        } else if (!inSeq && i != 0) {
            curProd *= i;
            inSeq = true;
        }
    }
    if (inSeq)
        ans += curProd;
    return ans;
}
void checkPossible() {
    vector<int> rows[MAXN];
    vector<int> cols[MAXN];
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            rows[i].push_back(grid[i][j]);
            cols[j].push_back(grid[i][j]);
        }
    }
    for (int i = 0; i < MAXN; i++) {
        int prod = getProd(rows[i]);
        cout << prod << ' ';
    }
    cout << endl;
    for (int i = 0; i < MAXN; i++) {
        int prod = getProd(cols[i]);
        cout << prod << ' ';
    }
    cout << endl;
}

vector<int> colVals = {28, 552, 64, 15, 86, 1304, 170, 81, 810};
vector<int> rowVals = {810, 585, 415, 92, 67, 136, 8, 225, 567};
bool checkPossiblehuh() {
    vector<int> rows[MAXN];
    vector<int> cols[MAXN];
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            rows[i].push_back(grid[i][j]);
            cols[j].push_back(grid[i][j]);
        }
    }
    for (int i = 0; i < MAXN; i++) {
        bool isFilled = true;
        for (auto j : rows[i]) {
            if (j == -1)
                isFilled = false;
        }
        int prod = getProd(rows[i]);
        if (isFilled) {
            if (prod != rowVals[i])
                return false;
        } else {
            if (prod > rowVals[i])
                return false;
        }
    }
    for (int i = 0; i < MAXN; i++) {
        bool isFilled = true;
        for (auto j : cols[i]) {
            if (j == -1)
                isFilled = false;
        }
        int prod = getProd(cols[i]);
        if (isFilled) {
            if (prod != colVals[i])
                return false;
        } else {
            if (prod > colVals[i])
                return false;
        }
    }
    if (!isConnected())
        return false;
    return true;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            cin >> grid[i][j];
        }
    }
    cout << isConnected() << endl;
    // checkPossible();
    cout << getAns() << endl;
    // cout << checkPossiblehuh() << endl;
    // dfs(0, 0);
    // for (int i = 0; i < MAXN; i++) {
    //     for (int j = 0; j < MAXN; j++) {
    //         cout << (vis[i][j]) << ' ';
    //     }
    //     cout << endl;
    // }
}