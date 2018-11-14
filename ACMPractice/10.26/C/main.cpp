#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 1e5 + 5;
int N;
vector<array<int, 3>> ranges;
set<int> vals;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        ranges.push_back({a, 0, i});
        ranges.push_back({b, 1, i});
    }
    sort(ranges.begin(), ranges.end());
    vector<int> ans;
    for (auto i : ranges) {
        if (i[1] == 1) {
            if (vals.find(i[2]) != vals.end()) {
                vals.clear();
                ans.push_back(i[0]);
            }
        } else {
            vals.insert(i[2]);
        }
    }
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i << ' ';
    }
    cout << endl;
}