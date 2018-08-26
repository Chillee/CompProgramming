#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef long long ll;
const ll MAXN = 10005;
const ll INF = 1e9;
vector<vector<string>> sentences;

ll N;
struct edge {
    ll a, b, cap, flow;
};

ll S, T, d[MAXN], ptr[MAXN], q[MAXN];
vector<edge> e;
vector<ll> g[MAXN];

void add_edge(ll a, ll b, ll cap) {
    edge e1 = {a, b, cap, 0};
    edge e2 = {b, a, 0, 0};
    g[a].push_back(e.size());
    e.push_back(e1);
    g[b].push_back(e.size());
    e.push_back(e2);
}

bool bfs() {
    ll qh = 0, qt = 0;
    q[qt++] = S;
    fill(d, d + N, -1);
    d[S] = 0;
    while (qh < qt && d[T] == -1) {
        ll v = q[qh++];
        for (ll i = 0; i < g[v].size(); ++i) {
            ll id = g[v][i], to = e[id].b;
            if (d[to] == -1 && e[id].flow < e[id].cap) {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[T] != -1;
}

ll dfs(ll v, ll flow) {
    if (!flow)
        return 0;
    if (v == T)
        return flow;
    for (; ptr[v] < (ll)g[v].size(); ++ptr[v]) {
        ll id = g[v][ptr[v]], to = e[id].b;
        if (d[to] != d[v] + 1)
            continue;
        ll pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
        if (pushed) {
            e[id].flow += pushed;
            e[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

ll dinic() {
    ll flow = 0;
    while (true) {
        if (!bfs())
            break;
        fill(ptr, ptr + N, 0);
        while (ll pushed = dfs(S, INF))
            flow += pushed;
    }
    return flow;
}
gp_hash_table<string, ll> mapping;
set<pair<ll, ll>> added;

void processEdge(string a, string b) {
    if (mapping.find(a) == mapping.end()) {
        mapping.insert({a, mapping.size()});
        mapping.insert({a + "O", mapping.size()});
        add_edge(mapping[a], mapping[a + "O"], 1);
    }
    if (mapping.find(b) == mapping.end()) {
        mapping.insert({b, mapping.size()});
        mapping.insert({b + "O", mapping.size()});
        add_edge(mapping[b], mapping[b + "O"], 1);
    }
    if (added.find({mapping[a], mapping[b]}) != added.end() || added.find({mapping[b], mapping[a]}) != added.end())
        return;
    if (a != "S" && a != "T") {
        add_edge(mapping[a + "O"], mapping[b], INF);
    } else {
        add_edge(mapping[a], mapping[b], INF);
    }
    if (b != "S" && b != "T") {
        add_edge(mapping[b + "O"], mapping[a], INF);
    } else {
        add_edge(mapping[b], mapping[a], INF);
    }
    added.insert({mapping[a], mapping[b]});
}

signed main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ll tests;
    cin >> tests;
    for (ll t = 1; t <= tests; t++) {
        sentences.clear();
        mapping.clear();
        added.clear();
        e.clear();
        fill(d, d + MAXN, 0), fill(ptr, ptr + MAXN, 0), fill(q, q + MAXN, 0);
        for (ll i = 0; i < MAXN; i++) {
            g[i].clear();
        }
        cin >> N;
        for (ll i = 0; i < N; i++) {
            vector<string> sentence;
            char t[15], t2;
            while (scanf("%s%c", &t, &t2) != EOF) {
                sentence.push_back(string(t));
                if (t2 == '\n')
                    break;
            }
            sentences.push_back(sentence);
        }
        mapping.insert({"S", 0});
        mapping.insert({"T", 1});
        for (auto i : sentences[0]) {
            processEdge("S", i);
        }
        for (auto i : sentences[1]) {
            processEdge(i, "T");
        }
        for (ll s = 2; s < sentences.size(); s++) {
            for (ll i = 0; i < sentences[s].size(); i++) {
                for (ll j = i + 1; j < sentences[s].size(); j++) {
                    processEdge(sentences[s][i], sentences[s][j]);
                }
            }
        }
        S = 0, T = 1, N = mapping.size();
        cout << "Case #" << t << ": " << dinic() << endl;
    }
}