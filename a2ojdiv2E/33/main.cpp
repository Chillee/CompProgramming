#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll A, B, K;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> A >> B >> K;
    ll cur = A;
    ll ans = 0;
    ll lcm = 1;
    for (ll i = 1; i <= K; i++) {
        lcm = lcm * i / __gcd(lcm, i);
    }
    while (cur % lcm != 0 && cur != B) {
        ll nxt = cur - 1;
        for (ll i = 2; i <= K; i++) {
            ll t = cur - (cur % i);
            if (t < B)
                continue;
            nxt = min(nxt, t);
        }
        cur = nxt;
        ans++;
    }
    int tcnt = 0;
    int tcur = lcm;
    while (tcur != 0) {
        ll nxt = tcur - 1;
        for (ll i = 2; i <= K; i++) {
            ll t = tcur - (tcur % i);
            nxt = min(nxt, t);
        }
        tcur = nxt;
        tcnt++;
    }
    ll cnt = max(0LL, ((cur - B - 3 * lcm) / lcm));
    cur -= cnt * lcm;
    ans += cnt * tcnt;
    while (cur != B) {
        ll nxt = cur - 1;
        for (ll i = 2; i <= K; i++) {
            ll t = cur - (cur % i);
            if (t < B)
                continue;
            nxt = min(nxt, t);
        }
        cur = nxt;
        ans++;
    }
    cout << ans << endl;
}