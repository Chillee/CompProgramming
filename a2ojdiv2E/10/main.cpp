#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e5 + 5;
const ll MAXBIT = 40;
ll N;
ll A[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    ll curLeft = 0;
    ll curRight = 0;
    for (ll i = 0; i < N; i++) {
        curLeft ^= A[i];
    }
    ll ans = curLeft;
    set<ll> possible;
    possible.insert(0);
    for (ll i = N - 1; i >= 0; i--) {
        curLeft ^= A[i];
        curRight ^= A[i];
        possible.insert(curRight);
        ll curVal = 0;
        for (ll j = MAXBIT; j >= 0; j--) {
            if ((curLeft & (1LL << j)) == 0) {
                curVal |= (1LL << j);
            }
            ll ub = curVal;
            for (ll k = j - 1; k >= 0; k--) {
                ub |= (1LL << k);
            }
            auto ubit = possible.upper_bound(ub);
            auto lbit = possible.lower_bound(curVal);
            if (ubit == lbit) {
                curVal ^= (1LL << j);
            }
        }
        ans = max(ans, curVal ^ curLeft);
    }
    cout << ans << endl;
}