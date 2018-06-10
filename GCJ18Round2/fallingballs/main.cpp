#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int MAXN = 105;
int T, C;
int B[MAXN];
vector<vector<char>> ans;
int main() {
    cin >> T;
    for (int t = 0; t < T; t++) {
        ans.clear();
        cin >> C;
        for (int i = 0; i < C; i++) {
            cin >> B[i];
        }
        if (B[0] == 0 || B[C - 1] == 0) {
            cout << "Case #" << t + 1 << ": IMPOSSIBLE" << endl;
            continue;
        }
        pii allocate[MAXN];
        int dest[MAXN] = {0};

        int curL = 0;
        for (int i = 0; i < C; i++) {
            if (B[i] > 0) {
                for (int j = curL; j < curL + B[i]; j++) {
                    dest[j] = i;
                }
                curL += B[i];
            }
        }
        vector<pii> cur;
        for (int i = 0; i < C; i++) {
            cur.push_back({1, dest[i]});
        }
        while (true) {
            vector<pii> next(C);
            vector<int> ch;
            vector<char> nextRow(C);
            bool changed = false;
            for (int i = 0; i < C; i++) {
                if (cur[i].second == i || cur[i].first == 0) {
                    next[i].first += cur[i].first;
                    next[i].second = cur[i].second;
                    // assert(next[i].second == cur[i].second);
                    nextRow[i] = '.';
                    continue;
                }
                if (cur[i].second < i) {
                    next[i - 1].first += cur[i].first;
                    next[i - 1].second = cur[i].second;
                    nextRow[i] = '/';
                    changed = true;
                } else if (cur[i].second > i) {
                    next[i + 1].first += cur[i].first;
                    next[i + 1].second = cur[i].second;
                    nextRow[i] = '\\';
                    changed = true;
                }
            }
            ans.push_back(nextRow);
            // for (auto i : cur) {
            //     cout << "(" << i.first << ", " << i.second << ") ";
            // }
            // cout << endl;
            if (!changed) {
                break;
            }
            cur = next;
        }
        // cout << ans.size() << ' ' << ans[0].size() << endl;
        // cout << "YO" << endl;
        cout << "Case #" << t + 1 << ": " << ans.size() << endl;
        for (auto i : ans) {
            for (auto j : i) {
                cout << j;
            }
            cout << endl;
        }
    }
}