#include <bits/stdc++.h>

using namespace std;

const int MAXN = 9;
int P;
struct cell {
    int val;
    char dirs[2]; // DR
};
cell grid[MAXN][MAXN];
vector<int> udin = {1, 3, 6, 8, 11, 13};
vector<int> lrin = {0, 2, 4, 5, 7, 9, 10, 12, 14};
unordered_set<int> rowVals[MAXN], colVals[MAXN];
unordered_set<int> boxVals[3][3];
bool isValid(int r, int c) { return r >= 0 && c >= 0 && r < MAXN && c < MAXN; }
bool checkConstraint(char constr, int a, int b) {
    if (a == 0 || b == 0)
        return true;
    if (constr == 0)
        return true;
    if (constr == '>')
        return a + b > 10;
    if (constr == '<')
        return a + b < 10;
    if (constr == '=')
        return a + b == 10;
    assert(false);
    return false;
}
void printGrid() {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            cout << grid[i][j].val << ' ';
        }
        cout << endl;
    }
}
bool isDone() {
    for (int i = 0; i < 9; i++) {
        if (rowVals[i].size() != 9 || colVals[i].size() != 9)
            return false;
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (boxVals[i / 3][j / 3].size() != 9)
                return false;
    return true;
}
bool backtrack() {
    if (isDone())
        return true;
    // printGrid();
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            // cout << i << ' ' << j << endl;
            if (grid[i][j].val != 0)
                continue;
            for (int k = 1; k <= MAXN; k++) {
                if (rowVals[i].count(k) || colVals[j].count(k) || boxVals[i / 3][j / 3].count(k))
                    continue;
                grid[i][j].val = k;
                bool good = true;
                if (isValid(i + 1, j)) {
                    good = good && checkConstraint(grid[i][j].dirs[0], grid[i + 1][j].val, grid[i][j].val);
                }
                if (isValid(i, j + 1)) {
                    good = good && checkConstraint(grid[i][j].dirs[1], grid[i][j + 1].val, grid[i][j].val);
                }
                if (isValid(i - 1, j))
                    good = good && checkConstraint(grid[i - 1][j].dirs[0], grid[i][j].val, grid[i - 1][j].val);
                if (isValid(i, j - 1))
                    good = good && checkConstraint(grid[i][j - 1].dirs[1], grid[i][j].val, grid[i][j - 1].val);
                if (!good) {
                    grid[i][j].val = 0;
                    continue;
                }
                rowVals[i].insert(k);
                colVals[j].insert(k);
                boxVals[i / 3][j / 3].insert(k);
                bool res = backtrack();
                if (res)
                    return res;
                rowVals[i].erase(k);
                colVals[j].erase(k);
                boxVals[i / 3][j / 3].erase(k);
                grid[i][j].val = 0;
            }
            return false;
        }
    }
    return false;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int p = 0; p < 1; p++) {
        int K;
        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                grid[i][j].val = 0;
                grid[i][j].dirs[0] = 0;
                grid[i][j].dirs[1] = 0;
            }
            rowVals[i].clear(), colVals[i].clear();
        }
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                boxVals[i][j].clear();
        for (int i = 0; i < 15; i++) {
            if (find(udin.begin(), udin.end(), i) != udin.end()) {
                int idx = find(udin.begin(), udin.end(), i) - udin.begin();
                for (int j = 0; j < 9; j++) {
                    char t;
                    cin >> t;
                    grid[(idx / 2) * 3 + (idx % 2)][j].dirs[0] = t;
                }
            } else {
                int idx = find(lrin.begin(), lrin.end(), i) - lrin.begin();
                for (int j = 0; j < 6; j++) {
                    char t;
                    cin >> t;
                    grid[idx][(j / 2) * 3 + (j % 2)].dirs[1] = t;
                }
            }
        }
        backtrack();
        printGrid();
    }
}