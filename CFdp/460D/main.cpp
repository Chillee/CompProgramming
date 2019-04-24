#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;
int N, M;
string S;
vector<int> adjlist[MAXN];
vector<int> pars[MAXN];
int order[MAXN];
int dp[MAXN][26];

bool vis[MAXN];
void topodfs(int cur, vector<int> &ans) {
    if (vis[cur])
        return;
    vis[cur] = true;
    for (auto i : adjlist[cur])
        topodfs(i, ans);
    ans.push_back(cur);
}
vector<int> toposort() {
    vector<int> ans;
    for (int i = 0; i < N; i++)
        topodfs(i, ans);
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    cin >> N >> M;
    cin >> S;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adjlist[a].push_back(b);
        pars[b].push_back(a);
    }
    auto res = toposort();
    for (int i = 0; i < res.size(); i++) {
        order[res[i]] = i;
    }
    for (int i = 0; i < N; i++) {
        for (auto j : adjlist[i]) {
            if (order[i] >= order[j]) {
                cout << -1 << endl;
                return 0;
            }
        }
    }
    for (auto i : res) {
        for (auto j : pars[i]) {
            for (int k = 0; k < 26; k++) {
                dp[i][k] = max(dp[j][k], dp[i][k]);
            }
        }
        dp[i][S[i] - 'a']++;
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 26; j++) {
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << endl;
    // for (auto i : res) {
    //     cout << i << ' ';
    // }
    // cout << endl;
}