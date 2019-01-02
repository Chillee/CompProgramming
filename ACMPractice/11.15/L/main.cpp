#include <bits/stdc++.h>

using namespace std;

map<pair<int, int>, vector<pair<int, int>>> lines;
vector<int> v;
int lis(vector<int> A) {
    vector<int> ans;
    for (auto x : A) {
        auto it = lower_bound(ans.begin(), ans.end(), x);
        if (it == ans.end())
            ans.push_back(x);
        else
            *it = x;
    }
    return ans.size();
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int Tx, Ty, N;
    cin >> Tx >> Ty >> N;
    for (int i = 0; i < N; i++) {
        int x, y, h;
        cin >> x >> y >> h;
        x -= Tx;
        y -= Ty;
        int d = __gcd(abs(x), abs(y));
        int xx = x / d;
        int yy = y / d;
        lines[{xx, yy}].push_back({d, h});
    }
    int cnt = 0;
    for (auto x : lines) {
        v.clear();
        sort(x.second.begin(), x.second.end());
        for (auto y : x.second) {
            v.push_back(y.second);
        }
        cnt += lis(v);
    }
    cout << cnt << endl;
}