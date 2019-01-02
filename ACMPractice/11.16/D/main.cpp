#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e3 + 5;
const ll INF = 1e15;

struct order {
    ll s, v, t;
    bool operator<(order x) { return make_tuple(s, v, t) < make_tuple(x.s, x.v, x.t); }
};
ll N, M, K;
vector<array<ll, 2>> adj[MAXN];
ll dist[MAXN][MAXN];
void dijkstra(ll start) {
    fill(begin(dist[start]), end(dist[start]), INF);
    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        if (dist[start][t[1]] <= t[0])
            continue;
        dist[start][t[1]] = t[0];
        for (auto i : adj[t[1]]) {
            pq.push({t[0] + i[0], i[1]});
        }
    }
}
vector<order> orders;

ll dp[MAXN];
ll base[MAXN];
bool f2(ll l) {
    base[0] = 0;
    for (ll i = 0; i < K; i++) {
        base[i + 1] = INF;
        ll time;
        ll curDist = dist[orders[i].v][0];
        ll worst = -orders[i].s;
        bool valid = true;
        for (ll j = i; j >= 0; j--) {
            time = max(base[j], orders[i].t) + dist[0][orders[j].v];
            valid = (time + worst) <= l;
            if (valid) {
                base[i + 1] = min(base[i + 1], time + curDist);
            }
            if (j > 0) {
                curDist += dist[orders[j - 1].v][orders[j].v];
                worst = max(-orders[j - 1].s, dist[orders[j - 1].v][orders[j].v] + worst);
            }
        }
        if (base[i + 1] == INF)
            return false;
    }
    return true;
}
ll binSearch(ll l, ll r) {
    if (abs(r - l) <= 5) {
        for (ll i = max(0ll, l - 5); i < r + 5; i++) {
            if (f2(i)) {
                return i;
            }
        }
        return r;
    }
    ll mid = (l + r) / 2;
    if (f2(mid)) {
        return binSearch(l, mid);
    } else {
        return binSearch(mid, r);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (ll i = 0; i < M; i++) {
        ll a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adj[a].push_back({d, b});
        adj[b].push_back({d, a});
    }
    for (ll i = 0; i < N; i++)
        dijkstra(i);
    cin >> K;
    for (ll i = 0; i < K; i++) {
        ll s, u, t;
        cin >> s >> u >> t;
        u--;
        orders.push_back({s, u, t});
    }
    // cout << f(6) << endl;
    cout << binSearch(0, 1e16) << endl;
}