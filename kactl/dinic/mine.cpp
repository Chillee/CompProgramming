#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template <class T = int> struct HLPP {
    const T INF = numeric_limits<T>::max();
    struct edge {
        int to, rev;
        T f;
    };
    vector<vector<edge>> adj;
    vector<vi> lst, gap;
    vector<T> excess;
    int highest, V;

    vi height, cnt;
    HLPP(int N) : V(N), adj(N), lst(N), gap(N), excess(N), height(N, V), cnt(N + 1) {}
    void addEdge(int from, int to, T f, bool isDirected = true) {
        adj[from].push_back({to, adj[to].size(), f});
        adj[to].push_back({from, adj[from].size() - 1, isDirected ? 0 : f});
    }
    void updHeight(int v, int nh) {
        if (height[v] != V)
            cnt[height[v]]--;
        height[v] = nh;
        if (nh == V)
            return;
        cnt[nh]++, highest = nh;
        gap[nh].push_back(v);
        if (excess[v] > 0)
            lst[nh].push_back(v);
    }
    void globalRelabel(int t) {
        height[t] = 0;
        queue<int> q({t});
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : adj[v]) {
                if (height[e.to] == V && adj[e.to][e.rev].f > 0)
                    q.push(e.to), updHeight(e.to, height[v] + 1);
            }
            highest = height[v];
        }
    }
    void push(int v, edge &e) {
        if (excess[e.to] == 0)
            lst[height[e.to]].push_back(e.to);
        T df = min(excess[v], e.f);
        cout << "adding: " << e.to << ' ' << df << endl;
        e.f -= df, adj[e.to][e.rev].f += df;
        excess[v] -= df, excess[e.to] += df;
    }
    void discharge(int v) {
        int nh = V;
        cout << "discharging: " << v << endl;
        for (auto &e : adj[v]) {
            if (e.f > 0) {
                if (height[v] == height[e.to] + 1) {
                    push(v, e);
                    if (excess[v] <= 0)
                        return;
                } else
                    nh = min(nh, height[e.to] + 1);
            }
        }
        if (cnt[height[v]] > 1)
            updHeight(v, nh);
        else {
            for (int i = height[v]; i <= highest; i++) {
                for (auto j : gap[i])
                    updHeight(j, V);
                gap[i].clear();
            }
        }
    }
    T calc(int s, int t) {
        fill(all(excess), 0);
        excess[s] = INF, excess[t] = -INF;
        globalRelabel(t);
        // for (int i=0; i<=highest; i++)
        //     cout<<lst[i].size()<<' ';
        // cout<<endl;
        cout << "INF: " << INF << endl;
        for (auto &e : adj[s])
            push(s, e);
        // for (int i=0; i<=highest; i++)
        for (int i = 0; i <= t; i++)
            cout << height[i] << " ";
        cout << endl;
        for (int i = 0; i <= t; i++)
            cout << excess[i] << " ";
        cout << endl;
        // cout<<endl;
        cout << "lsts: " << endl;
        for (int i = 0; i <= highest; i++) {
            if (!lst[i].empty()) {
                cout << i << ": ";
                for (auto j : lst[i])
                    cout << j << ' ';
                cout << endl;
            }
        }
        cout << endl;
        for (; highest >= 0; highest--) {
            while (!lst[highest].empty()) {
                int v = lst[highest].back();
                lst[highest].pop_back(), discharge(v);
                for (int i = 0; i <= t; i++)
                    cout << excess[i] << " ";
                cout << endl;
            }
            cout << "lsts: " << endl;
            for (int i = 0; i <= highest; i++) {
                if (!lst[i].empty()) {
                    cout << i << ": ";
                    for (auto j : lst[i])
                        cout << j << ' ';
                    cout << endl;
                }
            }
            cout << endl;
        }
        for (int i = 0; i <= t; i++)
            cout << excess[i] << " ";
        cout << endl;
        return excess[t] + INF;
    }
};

const int MAXN = 1e5 + 5;
void SPOJMATCHING() {
    int N, M, P;
    cin >> N >> M >> P;
    HLPP<> flow(N);
    // PushRelabel<ll, ll> flow(N + M + 5);
    for (int i = 0; i < N; i++)
        flow.addEdge(0, 2 + i, 1);
    for (int i = 0; i < M; i++)
        flow.addEdge(2 + N + i, 1, 1);
    for (ll i = 0; i < P; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        flow.addEdge(2 + a, 2 + b + N, 1);
    }
    cout << flow.calc(0, 1) << endl;
}
void LOJ() {
    int N, M, S, T;
    cin >> N >> M >> S >> T;
    HLPP<> flow(N);
    S--, T--;
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        flow.addEdge(a, b, c);
    }
    cout << flow.calc(S, T) << endl;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // SPOJMATCHING();
    LOJ();
}