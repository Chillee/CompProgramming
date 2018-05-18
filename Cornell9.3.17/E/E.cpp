#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
int N;
int ans[MAXN];
int A[MAXN];
vector<int> adj[MAXN];
map<int, int> cur_divs;
vector<int> divs;
int vis[MAXN];

int GCD(int a, int b) { return b ? GCD(b, a % b) : a; }

void dfs(int cur, int d) {
    if (vis[cur]) {
        return;
    }
    vis[cur] = true;
    for (int i = 0; i < divs.size(); i++) {
        cur_divs[divs[i]] += (A[cur] % divs[i] == 0);
        if (cur_divs[divs[i]] >= d) {
            ans[cur] = max(ans[cur], divs[i]);
        }
    }

    for (auto i : adj[cur]) {
        dfs(i, d + 1);
    }
    for (int i = 0; i < divs.size(); i++) {
        cur_divs[divs[i]] -= (A[cur] % divs[i] == 0);
    }
}

void dfs1(int cur, int par) {
    if (ans[cur]) {
        return;
    }
    ans[cur] = max(ans[cur], GCD(A[cur], par));
    for (auto i : adj[cur]) {
        dfs1(i, ans[cur]);
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int t = A[0];
    A[0] = 0;
    dfs1(0, 0);
    A[0] = t;
    for (int i = 0; i < N; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    int i = 1;
    while (i * i < A[0]) {
        if (A[0] % i == 0) {
            divs.push_back(i);
            divs.push_back(A[0] / i);
        }
        i += 1;
    }
    // dfs(0, 0);
    ans[0] = t;
    for (int i = 0; i < N; i++) {
        cout << ans[i] << ' ';
    }
    return 0;
}