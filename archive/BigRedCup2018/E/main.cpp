#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
int even[2 * MAXN];
int odd[2 * MAXN];
int N, M;
int V[MAXN];
int subTreeEnd[MAXN];
int origToTree[MAXN];
int isEven[MAXN];
vector<int> adjList[MAXN];

int t_idx = 0;
void preorder(int cur, int cur_depth) {
    int orig_idx = t_idx;
    origToTree[cur] = orig_idx;
    isEven[orig_idx] = cur_depth % 2 == 0;
    t_idx++;
    for (auto i : adjList[cur]) {
        if (origToTree[i] != -1)
            continue;
        preorder(i, cur_depth + 1);
    }
    subTreeEnd[orig_idx] = t_idx;
}

void modify(int l, int r, int val, bool curIsEven) {
    auto &tree = (curIsEven ? even : odd);
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            tree[l++] += val;
        if (r & 1)
            tree[--r] += val;
    }
}

int query(int p, bool curIsEven) {
    int res = 0;
    auto &tree = (curIsEven ? even : odd);
    for (p += N; p > 0; p >>= 1) {
        res += tree[p];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> V[i];
        origToTree[i] = -1;
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
    preorder(0, 0);

    for (int i = 0; i < M; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, val;
            cin >> x >> val;
            x--;
            int idx = origToTree[x];
            modify(idx, subTreeEnd[idx], val, isEven[idx]);
        } else if (t == 2) {
            int x;
            cin >> x;
            x--;
            int idx = origToTree[x];
            cout << query(idx, isEven[idx]) - query(idx, !isEven[idx]) + V[x] << endl;
        }
    }
}