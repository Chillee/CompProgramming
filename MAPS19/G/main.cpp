#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 5;
int N, M;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    int operator()(string x) const {
        int cur = 1;
        for (auto i : x)
            cur = hash_combine(cur, hash_f(i));

        return cur ^ RANDOM;
    }
};

vector<string> animals[MAXN];
string intend[MAXN];
vector<int> adj[MAXN];
int inDeg[MAXN], outDeg[MAXN];
gp_hash_table<string, int, chash> mapping;

template <int MAXN> struct SCC {
    int num[MAXN], low[MAXN];
    bool curProcess[MAXN];
    stack<int> curVis;
    int dfsCnt = 0;
    SCC() { fill(begin(num), end(num), -1), fill(begin(low), end(low), -1); }
    void dfs(int cur) {
        num[cur] = low[cur] = dfsCnt++;
        curProcess[cur] = true;
        curVis.push(cur);
        for (auto v : adj[cur]) {
            if (num[v] == -1)
                dfs(v);
            if (curProcess[v])
                low[cur] = min(low[cur], low[v]);
        }
        if (num[cur] == low[cur]) {
            while (curVis.top() != cur) {
                int t = curVis.top();
                curVis.pop();
                low[t] = low[cur];
                curProcess[t] = false;
            }
            curVis.pop();
            curProcess[cur] = false;
        }
    }
    void tarjans() {
        for (int i = 0; i < N; i++)
            if (num[i] == -1)
                dfs(i);
    }
};
SCC<MAXN> scc;
int clr[MAXN];
void dfs(int cur, int color) {
    if (clr[cur] != -1)
        return;
    clr[cur] = color;
    for (auto i : adj[cur])
        dfs(i, color);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill(begin(clr), end(clr), -1);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> intend[i];
        mapping[intend[i]] = i;
        int a;
        cin >> a;
        for (int j = 0; j < a; j++) {
            string s;
            cin >> s;
            animals[i].push_back(s);
        }
    }
    for (int i = 0; i < N; i++) {
        for (auto j : animals[i]) {
            int nxt = mapping[j];
            if (i == nxt)
                continue;
            adj[i].push_back(nxt);
            adj[nxt].push_back(i);
            inDeg[nxt]++;
            outDeg[i]++;
        }
    }
    // scc.tarjans();
    for (int i = 0; i < N; i++)
        dfs(i, i);
    int cur = -1;
    for (int i = 0; i < N; i++) {
        if (adj[i].size() > 0) {
            if (cur != -1 && clr[i] != cur) {
                cout << "Impossible" << endl;
                return 0;
            }
            cur = clr[i];
        }
    }
    int numMore = 0, numLess = 0;
    int changed = 0;
    for (int i = 0; i < N; i++) {
        if (inDeg[i] != 0 || outDeg[i] != 0)
            changed++;
        if (inDeg[i] == outDeg[i] + 1)
            numMore++;
        else if (inDeg[i] == outDeg[i] - 1)
            numLess++;
        else if (abs(inDeg[i] - outDeg[i]) > 1) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    if (changed == 0)
        cout << "FALSE ALARM" << endl;
    else if (numMore <= 1 && numLess <= 1)
        cout << "POSSIBLE" << endl;
    else
        cout << "IMPOSSIBLE" << endl;
}