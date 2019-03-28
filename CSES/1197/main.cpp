#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll INF = 1e18 + 5;
const ll MAXN = 2505;
ll N, M;
vector<array<ll, 3>> edges;
ll dist[MAXN], prv[MAXN];
void bellmanFord() {
    fill(dist, dist + MAXN, INF);
    fill(prv, prv + MAXN, 0);
    ll lst;
    for (ll i = 0; i < N; i++) {
        lst = -1;
        for (auto e : edges) {
            ll ndist = e[2] + dist[e[0]];
            if (ndist < dist[e[1]]) {
                dist[e[1]] = ndist;
                lst = e[1];
                prv[e[1]] = e[0];
            }
        }
    };
    if (lst == -1) {
        cout << "NO" << endl;
        return;
    } else {
        cout << "YES" << endl;
        for (ll i = 0; i < N; i++)
            lst = prv[lst];
        vector<ll> cycle;
        for (ll v = lst;; v = prv[v]) {
            cycle.push_back(v);
            if (v == lst && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());
        for (auto i : cycle)
            cout << i + 1 << ' ';
        cout << endl;
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
        edges.push_back({a, b, d});
    }
    bellmanFord();
}