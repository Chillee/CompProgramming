#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
ll N, K;
ll ans[MAXN];
ll powers[MAXN];
ll coins[MAXN];
pair<ll, ll> sortPow[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (ll i = 0; i < N; i++) {
        int t;
        cin >> t;
        sortPow[i] = {t, i};
    }
    for (ll j = 0; j < N; j++) {
        cin >> coins[j];
    }
    sort(sortPow, sortPow + N);
    multiset<ll> curCoins;
    for (ll i = 0; i < N; i++) {
        int realIdx = sortPow[i].second;
        ll cur = coins[realIdx];
        auto it = curCoins.rbegin();
        for (ll j = 0; j < min(K, (ll)curCoins.size()); j++) {
            cur += *it;
            it++;
        }
        curCoins.insert(coins[realIdx]);
        ans[realIdx] = cur;
    }
    for (ll i = 0; i < N; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}