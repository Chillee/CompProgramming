#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 1e5 + 5;

int N, M, P;
vector<int> adjList[MAXN];
int match[MAXN], dist[MAXN];
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
        for (auto i : adjList[u]) {
            if (dist[match[i]] == -1) {
                dist[match[i]] = dist[u] + 1;
                Q.push(match[i]);
            }
        }
    }
    return (dist[NIL] != -1);
}

bool dfs(int u) {
    for (auto v : adjList[u]) {
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
    cin >> N >> M >> P;
    for (int i = 0; i < P; i++) {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(N + b);
    }
    cout << hopcroft_karp() << endl;
}