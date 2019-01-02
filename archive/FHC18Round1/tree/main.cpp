#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int MAXN = 2005;
int T;
int K, N;
vector<int> tree[MAXN];
int color[MAXN];
vector<int> edge[MAXN];
vector<int> groups[MAXN];
int ans[MAXN];

void preorder(int cur, vector<int> &res) {
    res.push_back(cur);
    for (auto i : tree[cur]) {
        preorder(i, res);
    }
}

void postorder(int cur, vector<int> &res) {
    for (auto i : tree[cur]) {
        postorder(i, res);
    }
    res.push_back(cur);
}

void flood(int cur, int clr) {
    if (color[cur] != -1)
        return;
    color[cur] = clr;
    for (auto i : edge[cur]) {
        flood(i, clr);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> T;
    for (int t = 1; t <= T; t++) {
        for (int i = 0; i < MAXN; i++) {
            tree[i].clear();
            groups[i].clear();
            edge[i].clear();
        }
        fill(color, color + MAXN, -1);
        fill(ans, ans + MAXN, 1);
        cin >> N >> K;
        for (int i = 0; i < N; i++) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            if (a != -1) {
                tree[i].push_back(a);
            }
            if (b != -1) {
                tree[i].push_back(b);
            }
        }
        vector<int> pre;
        vector<int> post;
        preorder(0, pre);
        postorder(0, post);
        for (int i = 0; i < pre.size(); i++) {
            edge[pre[i]].push_back(post[i]);
            edge[post[i]].push_back(pre[i]);
        }
        for (int i = 0; i < N; i++) {
            flood(i, i);
        }

        for (int i = 0; i < N; i++) {
            groups[color[i]].push_back(i);
        }
        int curIdx = 0;
        bool isPossible = true;
        for (int i = 1; i <= K; i++) {
            while (groups[curIdx].size() == 0 && curIdx < N) {
                curIdx++;
            }
            if (curIdx == N) {
                isPossible = false;
                break;
            }
            for (auto j : groups[curIdx]) {
                ans[j] = i;
            }
            curIdx++;
        }
        cout << "Case #" << t << ": ";
        if (!isPossible) {
            cout << "Impossible" << endl;
        } else {
            for (int i = 0; i < N; i++) {
                cout << ans[i] << ' ';
            }
            cout << endl;
        }
    }
}