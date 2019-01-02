#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;
int N, M, Q;

int dist[MAXN];
int par[MAXN];
int color[MAXN];
int diameter[MAXN];
vector<int> adjlist[MAXN];
vector<int> colors;
vector<int> colorCats[MAXN];

int root(int v) { return par[v] < 0 ? v : (par[v] = root(par[v])); }
void merge(int x, int y) {
    if ((x = root(x)) == (y = root(y)))
        return;
    if (par[y] < par[x])
        swap(x, y);
    par[x] += par[y];
    par[y] = x;
}

void flood(int cur, int clr) {
    if (color[cur] != -1)
        return;
    color[cur] = clr;
    for (auto i : adjlist[cur]) {
        flood(i, clr);
    }
}
int getDepths(int cur, int depth) {
    if (dist[cur] != -1) {
        return -1;
    }
    dist[cur] = depth;
    int mxIdx = cur;
    for (auto i : adjlist[cur]) {
        int res = getDepths(i, depth + 1);
        if (res != -1 && dist[res] > dist[mxIdx]) {
            mxIdx = res;
        }
    }
    return mxIdx;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> Q;
    for (int i = 0; i < M; i++) {
        int a, b, d;
        cin >> a >> b;
        a--, b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    fill(color, color + N, -1);
    for (int i = 0; i < N; i++) {
        flood(i, i);
    }
    fill(par, par + N, -1);
    for (int i = 0; i < N; i++) {
        if (color[i] == i) {
            colors.push_back(i);
        }
        colorCats[color[i]].push_back(i);
        merge(i, color[i]);
    }

    for (auto c : colors) {
        for (auto i : colorCats[c]) {
            dist[i] = -1;
        }
        int start = getDepths(c, 0);
        for (auto i : colorCats[c]) {
            dist[i] = -1;
        }
        int end = getDepths(start, 0);
        int diam = dist[end];
        for (auto i : colorCats[c]) {
            diameter[i] = diam;
        }
    }
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 2) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            int oldA = root(a);
            int oldB = root(b);
            if (oldA == oldB)
                continue;
            merge(a, b);
            diameter[root(a)] =
                max(max(diameter[oldA], diameter[oldB]), (diameter[oldB] + 1) / 2 + (diameter[oldA] + 1) / 2 + 1);
        } else {
            int a;
            cin >> a;
            a--;
            cout << diameter[root(a)] << endl;
        }
    }
}