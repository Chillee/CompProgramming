#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 2e5 + 5;
ll N, H;
vector<array<ll, 2>> regions;
ll pref[MAXN];
bool check(ll mid) {
    // cout << "binsearch: " << mid << endl;
    for (ll i = 0; i < regions.size(); i++) {
        array<ll, 2> val = {regions[i][0] + mid - 1, (int)1e9 + 5};
        ll idx = lower_bound(regions.begin(), regions.end(), val) - regions.begin();
        if (idx != 0)
            idx--;
        ll curPref = (i == 0 ? 0 : pref[i - 1]);
        ll pIdxPref = (idx == 0 ? 0 : pref[idx - 1]);
        ll heightAfter = H - mid + pref[idx] - curPref;
        ll heightBefore = H - (regions[idx][0] - regions[i][0]) + pIdxPref - curPref;
        // cout << mid << ": " << heightAfter << ' ' << heightBefore << endl;
        if (heightAfter >= 0 && heightBefore > 0) {
            return true;
        }
    }
    return false;
}
ll binSearch(ll l, ll r) {
    if (abs(l - r) <= 5) {
        for (ll i = max(0ll, l - 5); i < r + 5; i++) {
            if (!check(i)) {
                return i - 1;
            }
        }
        return l;
    }
    ll mid = (l + r) / 2;
    // cout << l << ' ' << r << ' ' << mid << endl;
    if (check(mid)) {
        return binSearch(mid, r);
    } else {
        return binSearch(l, mid);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> H;
    for (ll i = 0; i < N; i++) {
        ll a, b;
        cin >> a >> b;
        regions.push_back({a, b});
    }
    pref[0] = regions[0][1] - regions[0][0];
    for (ll i = 1; i < regions.size(); i++) {
        pref[i] = pref[i - 1] + regions[i][1] - regions[i][0];
    }
    cout << binSearch(0, 2e11) << endl;
}