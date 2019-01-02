#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

char G[1005][1005];
int scores[1005][1005];
int N, M, K;
vector<pii> cur_nodes;
int dfs(int x, int y) {
    // cout << x << ' ' << y << ' ' << G[x][y] << endl;
    if (G[x][y] == 0 || G[x][y] == '*') {
        return 0;
    }
    G[x][y] = 0;
    cur_nodes.push_back(pii(x, y));
    int score = 0;
    if (G[x][y + 1] == '*') {
        score++;
    } else if (G[x][y + 1] == '.') {
        score += dfs(x, y + 1);
    }
    if (G[x][y - 1] == '*') {
        score++;
    } else if (G[x][y - 1] == '.') {
        score += dfs(x, y - 1);
    }
    if (G[x + 1][y] == '*') {
        score++;
    } else if (G[x + 1][y] == '.') {
        score += dfs(x + 1, y);
    }
    if (G[x - 1][y] == '*') {
        score++;
    } else if (G[x - 1][y] == '.') {
        score += dfs(x - 1, y);
    }
    return score;
}
int main() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> G[i][j];
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (G[i][j] == 0 || G[i][j] == '*') {
                continue;
            }
            cur_nodes.clear();
            int score = dfs(i, j);
            for (auto k : cur_nodes) {
                scores[k.first][k.second] = score;
            }
        }
    }
    cin.clear();
    for (int i = 0; i < K; i++) {
        int x, y;
        cin >> x >> y;
        cout << scores[x][y] << endl;
    }
}