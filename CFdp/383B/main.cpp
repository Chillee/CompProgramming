#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
int N, M, mxWeight;
int W[MAXN], B[MAXN];
vector<int> adjlist[MAXN];
vector<vector<int>> groups;
int color[MAXN];
int dp[MAXN][MAXN];

void dfscolor(int cur, int clr, vector<int> &group) {
    if (color[cur] != -1)
        return;
    color[cur] = clr;
    group.push_back(cur);
    for (auto i : adjlist[cur]) {
        dfscolor(i, clr, group);
    }
}

int main() {
    cin >> N >> M >> mxWeight;
    for (int i = 0; i < N; i++) {
        cin >> W[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    fill(color, color + MAXN, -1);
    for (int i = 0; i < N; i++) {
        vector<int> curGroup;
        dfscolor(i, i, curGroup);
        if (curGroup.size() > 0) {
            groups.push_back(curGroup);
        }
    }
    int sumW = 0, sumB = 0;
    for (int i = 0; i < groups[0].size(); i++) {
        int kw = W[groups[0][i]];
        int kb = B[groups[0][i]];
        dp[0][kw] = max(dp[0][kw], kb);
        sumW += kw, sumB += kb;
    }
    if (sumW <= mxWeight) {
        dp[0][sumW] = max(dp[0][sumW], sumB);
    }
    for (int i = 1; i < groups.size(); i++) {
        for (int j = 0; j <= mxWeight; j++) {
            int curW = 0, curB = 0;
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            for (int k = 0; k < groups[i].size(); k++) {
                int kw = W[groups[i][k]];
                int kb = B[groups[i][k]];
                curW += kw, curB += kb;
                if (j - kw < 0)
                    continue;
                dp[i][j] = max(dp[i][j], dp[i - 1][j - kw] + kb);
            }
            if (j - curW < 0)
                continue;
            dp[i][j] = max(dp[i][j], dp[i - 1][j - curW] + curB);
        }
    }
    int ans = 0;
    for (int i = 0; i <= mxWeight; i++) {
        ans = max(ans, dp[groups.size() - 1][i]);
    }
    cout << ans << endl;
}