#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 16;
typedef vector<array<int, 2>> state;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int RANDOM =
    (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    int operator()(state x) const {
        int cur = 5;
        for (auto i : x) {
            cur = hash_combine(cur, hash_combine(hash_f(i[0]), hash_f(i[1])));
        }
        return cur;
    }
};

int N, M;
bool grid[MAXN][MAXN];
vector<array<int, 2>> snake;
gp_hash_table<state, int, chash> vis;
array<int, 2> apple;
bool isValid(array<int, 2> pos, state curState) {
    if (pos[0] < 0 || pos[1] < 0 || pos[0] >= N || pos[1] >= M)
        return false;
    if (grid[pos[0]][pos[1]])
        return false;
    for (int i = 0; i < curState.size(); i++) {
        if (curState[i] == pos)
            return false;
    }
    return true;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char t;
            cin >> t;
            grid[i][j] = (t == '#');
            if (t > '0' && t <= '9') {
                snake.resize(max((int)snake.size(), t - '0'));
                snake[t - '1'] = {i, j};
            } else if (t == '@') {
                apple = {i, j};
            }
        }
    }
    state curState;
    curState = snake;
    queue<pair<int, state>> q;
    q.push({0, curState});
    while (q.size() > 0) {
        auto t = q.front();
        auto cur = t.second;
        auto dist = t.first;
        q.pop();
        if (vis.find(cur) != vis.end())
            continue;
        vis[cur] = dist;
        vector<array<int, 2>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        array<int, 2> curPos = cur[0];
        if (curPos == apple) {
            cout << dist << endl;
            return 0;
        }
        cur.pop_back();
        cur.insert(cur.begin(), cur[0]);
        for (auto i : dirs) {
            if (!isValid({curPos[0] + i[0], curPos[1] + i[1]}, cur))
                continue;
            cur[0] = {curPos[0] + i[0], curPos[1] + i[1]};
            q.push({dist + 1, cur});
            cur[0] = cur[1];
        }
    }
    cout << -1 << endl;
}