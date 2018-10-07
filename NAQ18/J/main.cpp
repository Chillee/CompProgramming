#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

int board[5][5];

bool isValid(int x, int y) { return (x <= y && y < 5 && x >= 0 && y >= 0); }
int rec() {
    int ans = -1e9;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x <= y; x++) {
            vector<array<int, 2>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}};
            for (auto dir : dirs) {
                if (!isValid(x + dir[0] * 2, y + dir[1] * 2))
                    continue;
                if (board[y + dir[1] * 2][x + dir[0] * 2] != 0)
                    continue;
                if (board[y + dir[1]][x + dir[0]] == 0 || board[y][x] == 0)
                    continue;
                int val = board[y + dir[1]][x + dir[0]];
                board[y + dir[1]][x + dir[0]] = 0;
                board[y + dir[1] * 2][x + dir[0] * 2] = board[y][x];
                board[y][x] = 0;
                int res = rec();
                board[y + dir[1]][x + dir[0]] = val;
                board[y][x] = board[y + dir[1] * 2][x + dir[0] * 2];
                board[y + dir[1] * 2][x + dir[0] * 2] = 0;
                ans = max(-res + val * board[y][x], ans);
            }
        }
    }
    if (ans == -1e9)
        return 0;
    return ans;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> board[i][j];
        }
    }
    cout << rec() << endl;
}