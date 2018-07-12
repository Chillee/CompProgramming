#include <bits/stdc++.h>

using namespace std;

typedef pair<bool, int> pii;
const int INF = 1 << 30;
const int MAXN = 1e5 + 5;
int N;
vector<int> adjlist[MAXN];
vector<int> children[MAXN];
bool vis[MAXN];

void root(int cur) {
    vis[cur] = true;
    for (int i : adjlist[cur]) {
        if (vis[i])
            continue;
        children[cur].push_back(i);
        root(i);
    }
}

pii solve(int cur) {
    if (children[cur].size() == 0) {
        return {false, 0};
    }
    vector<int> evens;
    vector<int> odds;
    for (auto i : children[cur]) {
        auto t = solve(i);
        if (t.first) {
            evens.push_back(t.second);
        } else {
            odds.push_back(t.second);
        }
    }
    sort(evens.begin(), evens.end(), greater<int>());
    sort(odds.begin(), odds.end(), greater<int>());
    int evenSum = 0;
    for (auto i : evens) {
        evenSum += i;
    }
    int oddSum = 0;
    for (auto i : odds) {
        oddSum += i;
    }
    if (odds.size() % 2 == 1) {
        return {true, oddSum + evenSum + evens.size()};
    } else {
        return {false, evenSum + oddSum + evens.size()};
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    root(0);
    auto res = solve(0);
    if (res.first) {
        cout << res.second << endl;
    } else {
        cout << -1 << endl;
    }
}