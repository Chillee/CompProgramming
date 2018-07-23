#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int MAXN = 3e5 + 5;
int N, M;
bool vis[MAXN];
map<int, int> dp[MAXN];
vector<tuple<int, int, int>> edges;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        edges.push_back({d, a, b});
    }
    sort(edges.begin(), edges.end());
    for (auto i : edges) {
        int a, b, d;
        tie(d, a, b) = i;
        auto lb = dp[a].lower_bound(d);
        int prevCnt = 1;
        if (lb != dp[a].begin()) {
            lb--;
            prevCnt = lb->second + 1;
        }
        auto nextb = dp[b].lower_bound(d);
        while (nextb != dp[b].end() && nextb->second <= prevCnt) {
            nextb = dp[b].erase(nextb);
        }
        nextb = dp[b].lower_bound(d);
        if (nextb != dp[b].begin()) {
            nextb--;
        }
        if (nextb == dp[b].end() || nextb->second <= prevCnt) {
            dp[b].insert({d, prevCnt});
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (auto j : dp[i]) {
            ans = max(ans, j.second);
        }
    }
    cout << ans << endl;
}