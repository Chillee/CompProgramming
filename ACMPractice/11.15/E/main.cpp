#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;
int N, M;
multiset<array<int, 2>> S;
array<int, 3> building[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        S.insert({t, i});
    }
    for (int i = 0; i < M; i++) {
        cin >> building[i][1];
        building[i][2] = i;
    }
    for (int i = 0; i < M; i++) {
        cin >> building[i][0];
    }
    sort(building, building + M);
    vector<array<int, 2>> ans;
    for (int i = 0; i < M; i++) {
        auto res = S.upper_bound({building[i][1], 100000});
        if (res == S.begin())
            continue;
        res--;
        // cout << building[i][1] << ' ' << *res << endl;
        ans.push_back({(*res)[1], building[i][2]});
        S.erase(res);
        // cout << S.size() << endl;
    }
    if (S.size() == 0) {
        sort(ans.begin(), ans.end());
        for (auto i : ans) {
            cout << i[1] + 1 << ' ';
        }
        cout << endl;
    } else {
        cout << "impossible" << endl;
    }
}