#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
typedef pair<int, int> pii;
int type[MAXN];
int ans[MAXN];
int N, T;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> type[i];
    }
    cin >> T;
    for (int i = 0; i < T; i++) {
        int t;
        cin >> t;
        t--;
        type[t] *= -1;
        ans[t] = -1;
    }
    stack<pii> cur;
    for (int i = 0; i < N; i++) {
        if (!cur.empty() && type[i] == -cur.top().first && type[i] < 0) {
            ans[i] = -1;
            ans[cur.top().second] = 1;
            cur.pop();
        } else {
            cur.push({type[i], i});
        }
    }
    stack<pii> cur2;
    while (!cur.empty()) {
        if (!cur2.empty() && cur2.top().first == -cur.top().first) {
            ans[cur2.top().second] = -1;
            ans[cur.top().second] = 1;
            cur2.pop();
        } else {
            cur2.push({-abs(cur.top().first), cur.top().second});
        }
        cur.pop();
    }
    if (cur2.size() > 0) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for (int i = 0; i < N; i++) {
            cout << ans[i] * abs(type[i]) << ' ';
        }
        cout << endl;
    }
}