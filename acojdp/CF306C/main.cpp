#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
// dp[i][j] = can you cross out some digits from first i digits s.t. result is j%8
string S;
bool dp[105][8];
pii prv[105][8];
bool used[105][8];
int main() {
    cin >> S;
    dp[0][0] = false;
    for (int i = 0; i < S.size(); i++) {
        for (int j = 0; j < 8; j++) {
            if (!dp[i][j])
                continue;
            int resMod = (j * 10 + S[i] - '0') % 8;
            dp[i + 1][j] = true;
            if (used[i][j]) {
                prv[i + 1][j] = {i, j};
            } else {
                prv[i + 1][j] = prv[i][j];
            }
            dp[i + 1][resMod] = true;
            used[i + 1][resMod] = true;
            if (used[i][j]) {
                prv[i + 1][resMod] = {i, j};
            } else {
                prv[i + 1][resMod] = prv[i][j];
            }
        }
        dp[i + 1][(S[i] - '0')%8] = true;
        prv[i + 1][(S[i] - '0')%8] = {0, 0};
        used[i + 1][(S[i] - '0')%8] = true;
    }
    if (!dp[S.size()][0])
        cout << "NO" << endl;
    else {
        for (int i = 1; i <= S.size(); i++) {
            if (dp[i][0]) {
                vector<char> ans;
                pii cur = {i, 0};
                while (cur.first != 0) {
                    ans.push_back(S[cur.first - 1]);
                    cur = prv[cur.first][cur.second];
                }
                cout << "YES" << endl;
                reverse(ans.begin(), ans.end());
                for (auto j : ans) {
                    cout << j;
                }
                cout << endl;
                exit(0);
            }
        }
    }
}