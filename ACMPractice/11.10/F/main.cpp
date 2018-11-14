#include <bits/stdc++.h>

using namespace std;

int T, N;
vector<pair<int, string>> cur;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cur.clear();
        cin >> N;
        map<string, int> cnt;
        for (int i = 0; i < N; i++) {
            string s;
            int c;
            cin >> s >> c;
            cnt[s] += c;
        }
        for (auto i : cnt) {
            cur.push_back({-i.second, i.first});
        }
        sort(cur.begin(), cur.end());
        cout << cur.size() << endl;
        for (auto i : cur) {
            cout << i.second << ' ' << -i.first << endl;
        }
    }
}