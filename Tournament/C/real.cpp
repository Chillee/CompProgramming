#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll N = 10000000;
ll lp[N + 1];
ll phi[N + 1];
vector<ll> pr;

void calc_sieve() {
    phi[1] = 1;
    for (ll i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            phi[i] = i - 1;
            pr.push_back(i);
        } else {
            // Calculating phi
            if (lp[i] == lp[i / lp[i]])
                phi[i] = phi[i / lp[i]] * lp[i];
            else
                phi[i] = phi[i / lp[i]] * (lp[i] - 1);
        }
        for (ll j = 0; j < (ll)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
            lp[i * pr[j]] = pr[j];
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    calc_sieve();
    ll N;
    cin >> N;
    ll ans = 0;
    for (ll i = 0; i <= N; i++) {
        ans += phi[i];
    }
    cout << ans * 2 - 1 << endl;
}