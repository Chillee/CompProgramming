// #include <bits/stdc++.h>

// using namespace std;

// const int MAXN = 100005;
// int N, M;
// int clr[MAXN];
// bool vis[MAXN];
// vector<int> adj[MAXN];

// bool dfs(int cur) {
//     if (vis[cur])
//         return true;
//     vis[cur] = true;
//     int res = true;
//     for (auto i : adj[cur]) {
//         if (clr[i] == -1) {
//             clr[i] = 1 - clr[cur];
//             res = res && dfs(i);
//         } else if (clr[i] == clr[cur]) {
//             return false;
//         }
//     }
//     return res;
// }

// int main() {
//     cin >> N >> M;
//     int start = 0;
//     for (int i = 0; i < M; i++) {
//         int a, b;
//         cin >> a >> b;
//         a--;
//         b--;
//         adj[a].push_back(b);
//         adj[b].push_back(a);
//     }
//     for (int t = 0; t < N; t++) {
//         for (int i = 0; i < MAXN; i++) {
//             clr[i] = -1;
//         }
//         if (vis[t])
//             continue;
//         clr[t] = 0;
//         bool is_bi = dfs(start);
//         vector<int> red;
//         vector<int> blue;
//         if (is_bi) {
//             for (int i = 0; i < N; i++) {
//                 if (clr[i] == 0) {
//                     blue.push_back(i);
//                 } else if (clr[i] == 1) {
//                     red.push_back(i);
//                 }
//             }
//             if (red.size() == 0 || blue.size() == 0) {
//                 continue;
//             }
//             cout << red.size() << endl;
//             for (auto i : red) {
//                 cout << i + 1 << ' ';
//             }
//             cout << endl;
//             cout << blue.size() << endl;
//             for (auto i : blue) {
//                 cout << i + 1 << ' ';
//             }
//             cout << endl;
//             return 0;
//         }
//     }
//     cout << -1 << endl;
// }
#include <bits/stdc++.h>

using namespace std;

vector<int> alist[100000];

int N, M;

int ans[100000];
vector<int> red;
vector<int> blue;

bool dfs(int cur, int clr) {
    if (ans[cur] == clr)
        return 1;
    if (ans[cur] == -clr)
        return 0;
    ans[cur] = clr;
    if (clr == -1) {
        red.push_back(cur);
    } else {
        blue.push_back(cur);
    }
    for (int j = 0; j < alist[cur].size(); j++) {
        if (!dfs(alist[cur][j], -clr))
            return 0;
    }
    return 1;
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        alist[a].push_back(b);
        alist[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        if (ans[i] == 0)
            if (!dfs(i, 1)) {
                cout << -1 << '\n';
                return 0;
            }
    }
    cout << red.size() << endl;
    for (int i = 0; i < N; i++) {
        if (ans[i] == -1)
            cout << i + 1 << endl;
    }
    cout << endl;
    cout << blue.size() << endl;
    for (int i = 0; i < N; i++) {
        if (ans[i] == 1)
            cout << i + 1 << ' ';
    }
    cout << endl;
}
