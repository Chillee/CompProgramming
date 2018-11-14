#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 2e5 + 5;
string S;
int Q;
int nxt[MAXN][26];
int curNxt[26];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    fill(curNxt, curNxt + 26, -1);
    for (int i = S.size(); i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            nxt[i][j] = curNxt[j];
        }
        if (i != 0)
            curNxt[S[i - 1] - 'a'] = i;
    }
    cin >> Q;
    stack<int> cur;
    cur.push(0);
    for (int i = 0; i < Q; i++) {
        string t;
        cin >> t;
        if (t == "push") {
            char c;
            cin >> c;
            int curPos = cur.top();
            if (curPos == -1) {
                cur.push(-1);
            } else {
                cur.push(nxt[curPos][c - 'a']);
            }
        } else {
            cur.pop();
        }
        cout << (cur.top() == -1 ? "NO" : "YES") << endl;
    }
}