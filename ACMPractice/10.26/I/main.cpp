#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2060;
const int MAXH = 26;
int N, H;
int tree[MAXH][MAXN];
int par[MAXN];
vector<int> levels[MAXH];
void setTree(int l, int i, int v) {
    if (tree[l][i] == 0)
        tree[l][i] = v;
    else
        tree[l][i + 1] = v;
}
vector<int> adj[MAXN];
bool vis[MAXN];
int dfs(int cur, int end, int depth) {
    if (vis[cur])
        return 1e9;
    vis[cur] = true;
    if (cur == end) {
        return depth;
    }
    int res = 1e9;
    for (auto i : adj[cur]) {
        res = min(res, dfs(i, end, depth + 1));
    }
    return res;
}
void construct(vector<int> tree) {
    for (int i = 1; i < tree.size(); i++) {
        if (i * 2 >= tree.size())
            break;
        adj[tree[i]].push_back(tree[i * 2 + 1]);
        adj[tree[i]].push_back(tree[i * 2]);
        adj[tree[i * 2]].push_back(tree[i]);
        adj[tree[i * 2 + 1]].push_back(tree[i]);
    }
}

int ask(int a, int b) {
    if (a == b)
        return 0;
    // fill(vis, vis + MAXN, false);
    // return dfs(a, b, 0);
    cout << "? " << a << ' ' << b << endl;
    int d;
    cin >> d;
    return d;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    // N = (1 << 10) - 1;
    // vector<int> realtree;
    // for (int i = 1; i <= N; i++) {
    //     realtree.push_back(i);
    // }
    // shuffle(realtree.begin(), realtree.end(), default_random_engine(2));
    // realtree.insert(realtree.begin(), 0);
    // construct(realtree);
    if (N == 1) {
        cout << "! 0" << endl;
        return 0;
    }
    int t = N + 1;
    while (t > 1) {
        t >>= 1;
        H++;
    }
    int mx = -1, mxIdx = -1;
    for (int i = 1; i <= N; i++) {
        int d = ask(1, i);
        if (d >= mx) {
            mxIdx = i;
            mx = d;
        }
    }
    assert(mx >= (H - 1));
    assert(mxIdx != -1);
    int mxIdx2 = -1;
    int mx2 = 0;
    for (int i = 1; i <= N; i++) {
        if (mxIdx == i)
            continue;
        assert(mxIdx > 0 && i > 0);
        int d = ask(mxIdx, i);
        mx2 = max(d, mx2);
        if (d == 2 * (H - 1)) {
            mxIdx2 = i;
            break;
        }
    }
    assert(mx2 == 2 * (H - 1));
    assert(mxIdx2 != -1);
    int root = -1;
    for (int i = 1; i <= N; i++) {
        if (mxIdx == i)
            continue;
        int d = ask(mxIdx, i);
        if (d == H - 1) {
            int d = ask(mxIdx2, i);
            if (d != H - 1)
                continue;
            root = i;
            break;
        }
    }
    if (root == -1)
        assert(false);
    levels[0].push_back(root);
    for (int i = 1; i <= N; i++) {
        if (root == i)
            continue;
        int d = ask(root, i);
        levels[d].push_back(i);
    }
    tree[0][0] = root;
    for (int i = 1; i < H; i++) {
        for (auto j : levels[i]) {
            int l = 0;
            int d;
            while (true) {
                assert(j != tree[i - 1][l]);
                int d = ask(j, tree[i - 1][l]);
                if (d == 1) {
                    setTree(i, l * 2, j);
                    break;
                } else {
                    l += (1 << ((d / 2) - 1));
                }
            }
        }
    }
    par[tree[0][0]] = 0;
    for (int i = 1; i < H; i++) {
        for (int j = 0; j < (1 << i); j++) {
            par[tree[i][j]] = tree[i - 1][j / 2];
        }
    }
    cout << "! ";
    for (int i = 1; i <= N; i++) {
        cout << par[i] << ' ';
    }
    cout << endl;
}