#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 9;
int grid[MAXN][MAXN];
vector<int> colVals = {28, 552, 64, 15, 86, 1304, 170, 81, 810};
vector<int> rowVals = {810, 585, 415, 92, 67, 136, 8, 225, 567};

bool canPlace(int x, int y) {
    if (x < 0 || y < 0 || x >= MAXN || y >= MAXN)
        return false;
    return grid[x][y] == -1;
}

ll next(ll x) {
    ll y = x + (1LL << (ffsll(x) - 1));
    x = x & ~y;
    while ((x & 1) == 0)
        x >>= 1;
    x >>= 1;
    return y | x;
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
bool vis[MAXN][MAXN];

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

bool checkPossible() {
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

pair<bool, vector<array<int, 2>>> genPoints(int x, int y, int n, int df, int ds, bool isHoriz) {
    vector<array<int, 2>> pts;
    int curX = x;
    int curY = y;
    if (isHoriz) {
        for (; abs(curX - x) < n; curX += df) {
            pts.push_back({curX, curY});
            if (!canPlace(curX, curY))
                return {false, {}};
        }
        for (curX -= df, curY += ds; abs(curY - y) < n; curY += ds) {
            pts.push_back({curX, curY});
            if (!canPlace(curX, curY))
                return {false, {}};
        }
    } else {
        for (; abs(curY - y) < n; curY += df) {
            pts.push_back({curX, curY});
            if (!canPlace(curX, curY))
                return {false, {}};
        }
        for (curY -= df, curX += ds; abs(curX - x) < n; curX += ds) {
            pts.push_back({curX, curY});
            if (!canPlace(curX, curY))
                return {false, {}};
        }
    }
    return {true, pts};
}

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

int cnt = 0;
bool backtrack(int rank) {
    if (!checkPossible()) {
        return false;
    }
    if (rank == 0) {
        cout << getAns() << endl;
        cnt++;
        return true;
    }
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            vector<int> dir = {-1, 1};
            for (auto f : dir) {
                for (auto s : dir) {
                    for (auto isH : {false, true}) {
                        auto pts = genPoints(i, j, rank, f, s, isH);
                        if (pts.first) {
                            bitset<MAXN * 2> chosePts(string(rank, '1'));
                            bitset<MAXN * 2> stopVal(string(rank, '1') + string(rank - 1, '0'));
                            while (chosePts.to_ullong() <= stopVal.to_ullong()) {
                                for (int mask = 0; mask < rank * 2 - 1; mask++) {
                                    if (chosePts[mask])
                                        grid[pts.second[mask][0]][pts.second[mask][1]] = rank;
                                    else
                                        grid[pts.second[mask][0]][pts.second[mask][1]] = 0;
                                }
                                backtrack(rank - 1);
                                for (auto pt : pts.second) {
                                    grid[pt[0]][pt[1]] = -1;
                                }
                                chosePts = bitset<MAXN * 2>(next(chosePts.to_ullong()));
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            grid[i][j] = -1;
        }
    }
    backtrack(9);
    cout << cnt << endl;
    // cout << res.first << endl;
    // for (auto i : res.second) {
    //     cout << i[0] << " " << i[1] << endl;
    // }
}