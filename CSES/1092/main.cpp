#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    if (N % 4 == 1 || N % 4 == 2) {
        cout << "NO" << endl;
        return 0;
    }
    ll val = N * (N + 1) / 4;
    set<ll> vals;
    for (ll i = N; i >= 1; i--) {
        if (val > i) {
            val -= i;
            vals.insert(i);
        } else {
            vals.insert(val);
            break;
        }
    }
    cout << "YES" << endl;
    cout << vals.size() << endl;
    for (auto i : vals) {
        cout << i << ' ';
    }
    cout << endl;
    cout << N - vals.size() << endl;
    for (ll i = 1; i <= N; i++) {
        if (vals.find(i) == vals.end())
            cout << i << ' ';
    }
    cout << endl;
}