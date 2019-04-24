#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N;
set<pair<int, int>> custs;
array<int, 2> inc[MAXN];
set<int> openRooms;
int ans[MAXN];
vector<tuple<int, bool, int>> events;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> inc[i][0] >> inc[i][1];
    for (int i = 0; i < N; i++) {
        events.push_back({inc[i][0], false, i});
        events.push_back({inc[i][1], true, i});
    }
    for (int i = 0; i < N; i++)
        openRooms.insert(i);
    sort(events.begin(), events.end());
    for (auto i : events) {
        if (get<1>(i)) {
            auto cur = custs.lower_bound({get<2>(i), 0});
            openRooms.insert(cur->second);
            custs.erase(cur);
        } else {
            custs.insert({get<2>(i), *openRooms.begin()});
            ans[get<2>(i)] = *openRooms.begin();
            openRooms.erase(openRooms.begin());
        }
    }
    int mx = 0;
    for (int i = 0; i < N; i++)
        mx = max(mx, ans[i]);
    cout << mx + 1 << endl;
    for (int i = 0; i < N; i++)
        cout << ans[i] + 1 << ' ';
    cout << endl;
}