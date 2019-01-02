#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e6 + 5;
ll N;
array<ll, 2> drives[MAXN];
bool cmp(array<ll, 2> a, array<ll, 2> b) {
    if (a[1] - a[0] >= 0 && b[1] - b[0] < 0) {
        return true;
    } else if (a[1] - a[0] < 0 && b[1] - b[0] >= 0) {
        return false;
    } else if (a[1] - a[0] >= 0 && b[1] - b[0] >= 0) {
        return a[0] < b[0];
    } else if (a[1] - a[0] < 0 && b[1] - b[0] < 0) {
        return a[1] > b[1];
    }
    assert(false);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> N) {
        fill(begin(drives), end(drives), array<ll, 2>());
        for (ll i = 0; i < N; i++) {
            ll a, b;
            cin >> a >> b;
            drives[i] = {a, b};
        }
        sort(drives, drives + N, cmp);
        ll cur = 0;
        ll ans = 0;
        for (ll i = 0; i < N; i++) {
            cur -= drives[i][0];
            ans = min(ans, cur);
            cur += drives[i][1];
        }
        cout << -ans << endl;
    }
}