#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
string S;
int idx[MAXN][4];
int prv[4];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    reverse(S.begin(), S.end());
    string chrs = "ACGT";
    for (int i = 0; i < 4; i++)
        prv[i] = -1;
    for (int i = 0; i < S.size(); i++) {
        for (int j = 0; j < 4; j++)
            idx[i][j] = prv[j];
        for (int j = 0; j < 4; j++) {
            if (chrs[j] == S[i])
                prv[j] = i;
        }
    }
    for (int i = 0; i < 4; i++)
        idx[S.size()][i] = prv[i];
    int cur = S.size();
    string ans;
    // for (int i = 0; i <= S.size(); i++) {
    //     for (int j = 0; j < 4; j++)
    //         cout << idx[i][j] << " ";
    //     cout << endl;
    // }
    while (cur != -1) {
        // cout << cur << endl;
        int nxt = MAXN;
        char nch;
        for (int i = 0; i < 4; i++) {
            if (idx[cur][i] < nxt)
                nxt = idx[cur][i], nch = chrs[i];
        }
        ans.push_back(nch);
        cur = nxt;
    }
    // reverse(ans.begin(), ans.end());
    // ans.push_back(ans[ans.size() - 1]);
    cout << ans << endl;
}