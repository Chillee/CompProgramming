#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N;
int par[MAXN];
vector<int> child[MAXN];
int subSize[MAXN];
vector<int> res;

int genSize(int cur) {
    int size = 1;
    for (auto i : child[cur]) {
        size += genSize(i);
    }
    subSize[cur] = size;
    return size;
}

void dfs(int cur) {
    vector<int> evens, odds;
    for (auto i : child[cur]) {
        if (subSize[i] % 2 == 0) {
            evens.push_back(i);
        } else {
            odds.push_back(i);
        }
    }
    for (auto i : evens) {
        dfs(i);
    }
    res.push_back(cur);
    for (auto i : odds) {
        dfs(i);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    int root = -1;
    for (int i = 0; i < N; i++) {
        int p;
        cin >> p;
        p--;
        if (p == -1)
            root = i;
        else
            child[p].push_back(i);
        par[i] = p;
    }
    if (N % 2 == 0) {
        cout << "NO" << endl;
        return 0;
    }
    genSize(root);
    dfs(root);
    cout << "YES" << endl;
    for (auto i : res) {
        cout << i + 1 << endl;
    }
    cout << endl;
}