#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

const int MAXN = 1e3 + 5;
vector<int> adj[MAXN];
int N, K;
vector<int> curP, wantP;
set<int> swantP, origP;
vector<int> connected[MAXN];
bool vis[MAXN];
void dfs(int cur, int start) {
    if (vis[cur])
        return;
    vis[cur] = true;

    if (swantP.find(cur) != swantP.end()) {
        connected[start].push_back(cur);
        // return;
    }
    if (cur != start && origP.find(cur) != origP.end())
        return;
    for (auto i : adj[cur]) {
        dfs(i, start);
    }
}
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
vector<int> path;
bool dfs2(int cur, int end) {
    if (vis[cur])
        return false;
    vis[cur] = true;
    if (cur == end) {
        path.push_back(end);
        return true;
    }
    for (auto i : adj[cur]) {
        bool res = dfs2(i, end);
        if (res) {
            path.push_back(cur);
            return true;
        }
    }
    return false;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int t;
        cin >> t;
        t--;
        curP.push_back(t);
        origP.insert(t);
    }
    for (int i = 0; i < K; i++) {
        int t;
        cin >> t;
        t--;
        wantP.push_back(t);
        swantP.insert(t);
    }
    for (int i = 0; i < N; i++) {
        string t;
        cin >> t;
        for (int j = 0; j < N; j++) {
            if (t[j] == '1') {
                adj[i].push_back(j);
            }
        }
    }
    for (auto s : curP) {
        fill(vis, vis + MAXN, false);
        dfs(s, s);
    }
    for (int i = 0; i < N; i++) {
        for (auto j : connected[i]) {
            adjList[i + 1].push_back(j + N + 1);
        }
    }
    int res = hopcroft_karp();
    if (res != K) {
        cout << "NO" << endl;
        return 0;
    }
    int ans = 0;
    vector<array<int, 2>> edges;
    for (int i = 1; i <= N; i++) {
        if (match[i] != NIL && origP.find(match[i] - N - 1) == origP.end()) {
            fill(begin(vis), end(vis), false);
            path.clear();
            dfs2(i - 1, match[i] - N - 1);
            reverse(path.begin(), path.end());
            ans += path.size() - 1;
            for (int j = 0; j < path.size() - 1; j++) {
                edges.push_back({path[j] + 1, path[j + 1] + 1});
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        if (match[i] != NIL && origP.find(match[i] - N - 1) != origP.end()) {
            fill(begin(vis), end(vis), false);
            path.clear();
            dfs2(i - 1, match[i] - N - 1);
            reverse(path.begin(), path.end());
            ans += path.size() - 1;
            for (int j = 0; j < path.size() - 1; j++) {
                edges.push_back({path[j] + 1, path[j + 1] + 1});
            }
        }
    }
    cout << "YES" << endl;
    cout << ans << endl;
    for (auto i : edges) {
        cout << i[0] << ' ' << i[1] << endl;
    }
}