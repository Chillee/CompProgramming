#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

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
    int operator()(int x) const { return hash_f(x); }
};

const int MAXN = 105;
int N, K;
int grid[MAXN][MAXN];
bool colVals[MAXN][MAXN];
set<int> colVal[MAXN];
vector<int> adjlist[2 * MAXN];
void genGraph(int k) {
    for (int i = 0; i < N; i++) {
        fill(colVals[i], colVals[i] + N, false);
    }
    fill(adjlist, adjlist + 2 * MAXN, vector<int>());
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < N; j++) {
            colVals[j][grid[i][j]] = true;
        }
    }
    for (int i = 0; i < N; i++) {
        colVal[i].clear();
    }
    for (int j = 0; j < N; j++) {
        for (int v = 1; v <= N; v++) {
            if (!colVals[j][v]) {
                // cout << "taking: " << j << ' ' << v << endl;
                colVal[j].insert(v);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (auto j : colVal[i]) {
            adjlist[i + 1].push_back(j + N);
            // adjlist[j + N].push_back(i + 1);
        }
    }
}

int match[MAXN * 2], dist[MAXN * 2];
const int NIL = 0;

bool bfs() {
    queue<int> Q;
    fill(begin(dist), end(dist), -1);
    for (int i = 1; i <= N; i++) {
        if (match[i] == NIL) {
            dist[i] = 0;
            Q.push(i);
        }
    }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto i : adjlist[u]) {
            if (dist[match[i]] == -1) {
                dist[match[i]] = dist[u] + 1;
                Q.push(match[i]);
            }
        }
    }
    return (dist[NIL] != -1);
}

bool dfs(int u) {
    for (auto v : adjlist[u]) {
        if (match[v] == NIL || (dist[match[v]] == dist[u] + 1 && dfs(match[v]))) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int hopcroft_karp() {
    int matching = 0;
    fill(begin(match), end(match), NIL);
    while (bfs()) {
        for (int i = 1; i <= N; i++)
            if (match[i] == NIL && dfs(i))
                matching++;
    }
    return matching;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = K; i < N; i++) {
        genGraph(i);
        int res = hopcroft_karp();
        if (res != N) {
            cout << "no" << endl;
            return 0;
        }
        for (int j = 1; j <= N; j++) {
            grid[i][j - 1] = match[j] - N;
        }
    }
    for (int i = 0; i < N; i++) {
        set<int> rvals;
        set<int> cvals;
        for (int j = 0; j < N; j++) {
            rvals.insert(grid[i][j]);
            cvals.insert(grid[j][i]);
        }
        if (rvals.size() != N || cvals.size() != N) {
            cout << "no" << endl;
            return 0;
        }
    }
    cout << "yes" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
}