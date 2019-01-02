#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int INF = 1e9;
const int MAXN = 2e5 + 5;
struct edge {
    int b;
    int d;
    int idx;
};
int N, M;
vector<edge> adjlist[MAXN];
int flow[MAXN];
int ans[MAXN];
int sumEdges[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adjlist[a].push_back({b, d, i});
        adjlist[b].push_back({a, d, -i});
    }
    for (int i = 0; i < N; i++) {
        for (auto j : adjlist[i]) {
            sumEdges[i] -= j.d;
        }
    }
    flow[0] = 1e9;
    flow[N - 1] = -1e9;
    queue<int> process;
    process.push(0);
    while (process.size()) {
        int cur = process.front();
        process.pop();
        for (auto i : adjlist[cur]) {
            if (ans[abs(i.idx)] != 0)
                continue;
            flow[i.b] += i.d;
            sumEdges[i.b] += i.d;
            ans[abs(i.idx)] = i.idx;
            if (flow[i.b] == -sumEdges[i.b]) {
                process.push(i.b);
            }
        }
    }
    for (int i = 1; i <= M; i++) {
        cout << (ans[i] < 0) << endl;
    }
}