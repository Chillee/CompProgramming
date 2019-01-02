#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150;
const int INF = 1e9;

struct MinCostFlow {
    const static int MAXV = MAXN;
    const int INF = 1e9 + 5;
    const int s = MAXV - 2, t = MAXV - 1;
    struct edge {
        int from, to, cap, flow, cost;
    };

    int cost[MAXV][MAXV];
    vector<edge> edges;
    int dist[MAXV];
    int par[MAXV];

    int minCost(int flow) {
        int result = 0;
        while (true) {
            fill(begin(dist), end(dist), INF);
            dist[s] = 0;
            while (true) {
                bool change = false;
                for (int i = 0; i < edges.size(); i++) {
                    edge e = edges[i];
                    if (e.flow == e.cap || dist[e.from] == INF)
                        continue;
                    if (dist[e.to] > dist[e.from] + e.cost) {
                        dist[e.to] = dist[e.from] + e.cost;
                        par[e.to] = i;
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
                edge tmp = edges[par[cur]];
                int from = tmp.from, can_push = tmp.cap - tmp.flow;
                push = min(push, can_push);
                cur = from;
            }

            flow -= push;
            cur = t;
            while (cur != s) {
                edge tmp = edges[par[cur]];
                int from = tmp.from;
                edges[par[cur]].flow += push;
                edges[par[cur] ^ 1].flow -= push;
                result += push * tmp.cost;
                cur = from;
            }

            if (flow == 0)
                break;
        }
        return result;
    }

    void addEdge(int from, int to, int cap, int cost) {
        edges.push_back({from, to, cap, 0, cost});
        edges.push_back({to, from, cap, cap, -cost});
    }
};

string T;
int N;
string S[MAXN];
int A[MAXN];
MinCostFlow flow;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> S[i] >> A[i];
    }
    for (int i = 0; i < N; i++) {
        flow.addEdge(flow.s, i, A[i], i + 1);
    }
    for (int i = 0; i < N; i++) {
        vector<int> cnt(26);
        for (auto j : S[i]) {
            cnt[j - 'a']++;
        }
        for (int j = 0; j < 26; j++) {
            if (cnt[j] == 0)
                continue;
            flow.addEdge(i, N + j, cnt[j], 0);
        }
    }

    vector<int> cnt(26);
    for (auto i : T) {
        cnt[i - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (cnt[i] == 0)
            continue;
        flow.addEdge(N + i, flow.t, cnt[i], 0);
    }
    cout << flow.minCost(T.size()) << endl;
}