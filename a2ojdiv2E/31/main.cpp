#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N, A, B;
set<ll> X;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        ll t;
        cin >> t;
        X.insert(t);
    }
    cin >> A >> B;
    ll ans = 0;
    ll cur = A;
    ll nxt = A - 1;
    while (cur != B) {
        // while (X.size() && *X.rbegin() >= cur) {
        //     X.erase(*X.rbegin());
        // }
        vector<int> toRemove;
        for (auto i : X) {
            ll t = cur - (cur % i);
            if (t < B) {
                toRemove.push_back(i);
                continue;
            }
            nxt = min(nxt, t);
        }
        for (auto i : toRemove) {
            X.erase(i);
        }
        cur = nxt;
        nxt = cur - 1;
        ans++;
    }
    cout << ans << endl;
}