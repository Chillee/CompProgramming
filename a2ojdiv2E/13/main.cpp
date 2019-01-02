#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
typedef pair<int, int> pii;
// #define unordered_set set

int N, K;
vector<pii> adjlist[MAXN];
int ans[MAXN];
bool vis[MAXN];
set<int> fools[MAXN];
void dfs(int cur) {
    vector<set<int> *> sets;
    sets.push_back(&fools[cur]);
    for (auto i : adjlist[cur]) {
        if (vis[i.first])
            continue;
        vis[i.first] = true;
        dfs(i.first);
        ans[i.second] = fools[i.first].size();
        sets.push_back(&fools[i.first]);
    }
    sort(sets.begin(), sets.end(), [](set<int> *a, set<int> *b) { return a->size() > b->size(); });
    for (int j = 1; j < sets.size(); j++) {
        for (auto k : *(sets[j])) {
            if (sets[0]->find(k) == sets[0]->end()) {
                sets[0]->insert(k);
            } else {
                sets[0]->erase(k);
            }
        }
    }
    swap(*(sets[0]), fools[cur]);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adjlist[a].push_back({b, i});
        adjlist[b].push_back({a, i});
    }
    cin >> K;
    for (int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (a == b) {
            continue;
        }
        fools[a].insert(i);
        fools[b].insert(i);
    }
    vis[0] = true;
    dfs(0);
    for (int i = 0; i < N - 1; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}