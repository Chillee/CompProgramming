#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
const ll MAXN = 2005;
ll N, K;
array<ll, 3> F[MAXN];
multiset<array<ll, 2>> F2;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (ll i = 0; i < N; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        F[i] = {a, b, c};
    }
    sort(F, F + N);
    ll ans = 1e18 + 5;
    for (ll i = 0; i < N; i++) {
        F2.insert({F[i][1], F[i][2]});
        if (F2.size() >= K) {
            multiset<ll> finals;
            for (auto j : F2) {
                finals.insert(j[1]);
                while (finals.size() > K) {
                    finals.erase(--finals.end());
                }
                if (finals.size() == K) {
                    ans = min(ans, F[i][0] + j[0] + *finals.rbegin());
                }
            }
        }
    }
    cout << ans << endl;
}