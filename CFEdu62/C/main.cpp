#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 3e5 + 5;
array<ll, 2> songs[MAXN];
ll N, K;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (ll i = 0; i < N; i++)
        cin >> songs[i][0] >> songs[i][1];
    sort(songs, songs + N, [](auto a, auto b) { return a[1] > b[1]; });
    multiset<ll> curLengths;
    ll sm = 0;
    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        curLengths.insert(songs[i][0]);
        sm += songs[i][0];
        if (curLengths.size() > K) {
            sm -= *curLengths.begin();
            curLengths.erase(curLengths.begin());
        }
        ans = max(ans, sm * songs[i][1]);
    }
    cout << ans << endl;
}