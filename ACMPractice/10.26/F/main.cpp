#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

const int MAXN = 1e3 + 5;
int N;
set<int> A[MAXN];
set<int> orig[MAXN];
set<int> check[MAXN];
vector<array<int, 2>> edges;

set<int> cur, nxt;
vector<int> adj[MAXN];
void dfs(int cur, int start) {
    check[start].insert(cur);
    for (auto i : adj[cur]) {
        dfs(i, start);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int c;
        cin >> c;
        for (int j = 0; j < c; j++) {
            int t;
            cin >> t;
            t--;
            A[t].insert(i);
            orig[i].insert(t);
        }
    }
    for (int i = 0; i < N; i++) {
        if (A[i].size() == 0) {
            cur.insert(i);
        }
    }
    if (cur.size() > 1) {
        cout << "NO" << endl;
        return 0;
    }
    while (true) {
        bool allDone = true;
        for (int i = 0; i < N; i++) {
            if (A[i].size() == 1) {
                allDone = false;
                if (cur.find(*A[i].begin()) != cur.end()) {
                    edges.push_back({*A[i].begin(), i});
                    nxt.insert(i);
                } else {
                    cout << "NO" << endl;
                    return 0;
                }
            }
        }
        for (int i = 0; i < N; i++) {
            if (A[i].size() == 0)
                continue;
            int cnt = 0;
            for (auto j : cur) {
                if (A[i].find(j) != A[i].end()) {
                    A[i].erase(j);
                    cnt++;
                }
            }
            if (cnt > 1) {
                cout << "NO" << endl;
                return 0;
            }
        }
        if (allDone)
            break;
        cur = nxt;
        nxt.clear();
    }
    for (int i = 0; i < N; i++) {
        if (!A[i].empty()) {
            cout << "NO" << endl;
            return 0;
        }
    }
    if (edges.size() != N - 1) {
        cout << "NO" << endl;
        return 0;
    }
    for (auto i : edges) {
        adj[i[0]].push_back(i[1]);
    }
    for (int i = 0; i < N; i++) {
        dfs(i, i);
    }
    for (int i = 0; i < N; i++) {
        // cout << orig[i].size() << ' ' << check[i].size() << endl;
        if (orig[i].size() + 1 != check[i].size()) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    for (auto i : edges) {
        cout << i[0] + 1 << ' ' << i[1] + 1 << endl;
    }
}