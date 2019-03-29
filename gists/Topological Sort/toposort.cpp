bool vis[MAXN];

void topodfs(int cur, vector<int> &ans) {
    if (vis[cur])
        return;
    vis[cur] = true;
    for (auto i : adjlist[cur]) {
        topodfs(i, ans);
    }
    ans.push_back(cur);
}

vector<int> toposort() {
    vector<int> ans;
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            topodfs(i, ans);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}