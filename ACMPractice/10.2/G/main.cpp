#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
ll T;
ll A, B, M;

ll egcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = egcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

map<ll, ll> smallStep;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll x, y;
    cin >> T;
    for (ll t = 0; t < T; t++) {
        smallStep.clear();
        cin >> A >> B >> M;
        A %= M;
        B %= M;
        ll cur = 1;
        smallStep[1] = 0;
        ll root = (ll)sqrt(M) + 1;
        for (ll i = 1; i <= root; i++) {
            cur *= A;
            cur %= M;
            smallStep[cur] = i;
        }
        ll bigStep = cur;
        cur = 1;
        for (ll i = 0; i <= M; i += root) {
            ll p = cur;
            cur *= bigStep;
            cur %= M;
            ll x, y;
            int d = egcd(p, M, x, y);
            if (B % d != 0)
                continue;
            x = ((x % M) + M) % M;
            ll q = x * (B / d);
            q = ((q % M) + M) % M;
            if (smallStep.find(q) != smallStep.end()) {
                cout << i + smallStep[q] << endl;
                break;
            }
        }
    }
}