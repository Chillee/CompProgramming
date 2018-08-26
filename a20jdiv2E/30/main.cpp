#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150;
const int INF = 1e9;

struct edge {
    int from, to, cap, flow, cost;
};

int cost[MAXN][MAXN];
vector<edge> e;
int dist[MAXN];
int par[MAXN];
int s, t, numNodes;

int minCost(int flow) {
    int result = 0;
    while (true) {
        fill(dist, dist + numNodes, INF);
        dist[s] = 0;
        while (true) {
            bool change = false;
            for (int i = 0; i < e.size(); i++) {
                int from = e[i].from, to = e[i].to;
                if (e[i].flow == e[i].cap)
                    continue;
                if (dist[from] == INF)
                    continue;
                if (dist[to] > dist[from] + e[i].cost) {
                    dist[to] = dist[from] + e[i].cost;
                    par[to] = i;
                    change = true;
                }
            }
            if (!change)
                break;
        }

        if (dist[t] == INF) {
            return -1;
        }

        int push = flow;
        int cur = t;
        while (cur != s) {
            edge tmp = e[par[cur]];
            int from = tmp.from, can_push = tmp.cap - tmp.flow;
            push = min(push, can_push);
            cur = from;
        }

        flow -= push;
        cur = t;
        while (cur != s) {
            edge tmp = e[par[cur]];
            int from = tmp.from;
            e[par[cur]].flow += push;
            e[par[cur] ^ 1].flow -= push;
            result += push * tmp.cost;
            cur = from;
        }

        if (flow == 0)
            break;
    }
    return result;
}

void addEdge(int from, int to, int cap, int cost) {
    e.push_back({from, to, cap, 0, cost});
    e.push_back({to, from, cap, cap, -cost});
}

string T;
int N;
string S[MAXN];
int A[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> S[i] >> A[i];
    }
    for (int i = 0; i < N; i++) {
        addEdge(0, 2 + i, A[i], i + 1);
    }
    for (int i = 0; i < N; i++) {
        vector<int> cnt(26);
        for (auto j : S[i]) {
            cnt[j - 'a']++;
        }
        for (int j = 0; j < 26; j++) {
            if (cnt[j] == 0)
                continue;
            addEdge(2 + i, 2 + N + j, cnt[j], 0);
        }
    }

    vector<int> cnt(26);
    for (auto i : T) {
        cnt[i - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (cnt[i] == 0)
            continue;
        addEdge(2 + N + i, 1, cnt[i], 0);
    }
    s = 0, t = 1, numNodes = 2 + N + 26;
    cout << minCost(T.size()) << endl;
}