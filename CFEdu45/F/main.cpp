#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair<int, int> pii;

const int MAXN = 2e5 + 5;
int N, M;
int S[MAXN];
vector<pii> adjlist[MAXN];
vector<pii> children[MAXN];
int sumTree[MAXN];
int result[MAXN];
bool vis[MAXN];

int dfs(int cur) {
    int sum = S[cur];
    for (auto i : adjlist[cur]) {
        if (vis[i.first]) {
            continue;
        }
        vis[i.first] = true;
        children[cur].push_back(i);
        sum += dfs(i.first);
    }
    sumTree[cur] = sum;
    return sum;
}

void dfs2(int cur) {
    for (auto i : children[cur]) {
        if (i.second > 0) {
            result[i.second] = sumTree[i.first];
        } else {
            result[-i.second] = -sumTree[i.first];
        }
        dfs2(i.first);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    cin >> M;
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adjlist[a].push_back({b, i});
        adjlist[b].push_back({a, -i});
    }
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += S[i];
    }
    vis[0] = true;
    dfs(0);
    if (sumTree[0] != 0) {
        cout << "Impossible" << endl;
        return 0;
    }
    dfs2(0);
    cout << "Possible" << endl;
    for (int i = 1; i <= M; i++) {
        cout << result[i] << endl;
    }
}