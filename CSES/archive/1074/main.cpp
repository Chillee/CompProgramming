#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 5e+5;
ll N;
ll P[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++)
        cin >> P[i];
    sort(P, P + N);
    ll med = P[N / 2];
    ll ans = 1e18 + 5;
    for (int i = med - 1; i <= med + 1; i++) {
        ll cur = 0;
        for (int j = 0; j < N; j++)
            cur += abs(P[j] - i);
        ans = min(ans, cur);
    }
    cout << ans << endl;
}