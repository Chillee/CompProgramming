#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3005;
int N, Q;
int A[MAXN];
int dp[MAXN][MAXN];
int tmp[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    map<int, int> comp;
    for (int i = 0; i < N; i++)
        comp[A[i]] = i;
    int cnt = 0;
    for (auto i : comp)
        A[i.second] = cnt++;
    for (int i = 0; i < N; i++)
        dp[i][A[i]] = 1;
    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        for (int j = 0; j < cnt; j++)
            tmp[j] = dp[a][j];
        for (int j = 0; j < cnt; j++)
            dp[a][j] += dp[b][j];
        for (int j = 0; j < cnt; j++)
            dp[b][j] += tmp[j];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < cnt; j++)
                cout << dp[i][j] << ' ';
            cout << endl;
        }
    }
}