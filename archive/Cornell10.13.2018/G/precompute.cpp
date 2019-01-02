
#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

const int MAXN = 45;
bool board[MAXN][MAXN];
int N, M;
vector<array<int, 2>> dirs = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool isValid(int x, int y) { return x >= 0 && y >= 0 && x < N && y < M; }
vector<int> add(int x, int y) {
    vector<int> changed;
    for (int j = 0; j < dirs.size(); j++) {
        auto i = dirs[j];
        if (isValid(x + i[0], y + i[1]) && board[x + i[0]][y + i[1]] == false) {
            board[x + i[0]][y + i[1]] = true;
            changed.push_back(j);
        }
    }
    return changed;
}
int bestSol = 1e5 + 5;
void rec(int depth) {
    if (depth >= bestSol)
        return;
    int ans = 1e5;
    bool allSet = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j])
                continue;
            // cout << depth << endl;
            allSet = false;
            auto t = add(i, j);
            rec(depth + 1);
            for (auto l : t) {
                board[i + dirs[l][0]][j + dirs[l][1]] = false;
            }
        }
    }
    if (allSet) {
        bestSol = depth;
        return;
    }
    return;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    rec(0);
    cout << N * M - bestSol << endl;
    // int maxBoard = 3;
    // for (int i = 1; i <= maxBoard; i++) {
    //     cout << '{';
    //     for (int j = 1; j <= maxBoard; j++) {
    //         N = i, M = j;
    //         int ans = rec();
    //         cout << N * M - ans;
    //         if (j != maxBoard)
    //             cout << ',';
    //     }
    //     cout << "}," << endl;
    // }
    // cout << endl;
}