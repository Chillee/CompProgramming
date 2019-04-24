#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
string S;
int idx[MAXN];
vector<array<int, 2>> mp;
int fl[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == '#')
            S[i] = 'a' - 1;
        mp.push_back({S[i] - 'a', i});
    }
    sort(mp.begin(), mp.end());
    for (int i = -1; i < 26; i++) {
        vector<int> cPos;
        for (int j = 0; j < mp.size(); j++)
            if (mp[j][0] == i)
                cPos.push_back(j);
        int cnt = 0;
        for (int j = 0; j < S.size(); j++) {
            if (S[j] - 'a' == i) {
                fl[cPos[cnt++]] = j;
            }
        }
    }
    string ans = "#";
    int cur = fl[0];
    while (cur != 0) {
        ans.push_back(mp[cur][0] + 'a');
        cur = fl[cur];
    }
    cout << ans.substr(1) << endl;
}