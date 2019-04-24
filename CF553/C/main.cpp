#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

const int MOD = 1e9 + 7;
const int bits = 10;
const int po = 1 << bits;
// if all numbers are less than 2ˆk , set bits = 64−k
ull modMul(ull a, ull b) {
    ull x = a * (b & (po - 1)) % MOD;
    while ((b >>= bits) > 0) {
        a = (a << bits) % MOD;
        x += (a * (b & (po - 1))) % MOD;
    }
    return x % MOD;
}
ull binExp(ull b, ull pw) {
    if (pw == 0)
        return 1;
    return modMul(binExp(modMul(b, b), pw / 2), (pw & 1 ? b : 1));
};
ll mod_inv(ll a) { return binExp(a, MOD - 2); }

ll sumCons(ll n) {
    ll cur = modMul(n, (n + 1));
    return modMul(cur, mod_inv(2));
}
ll sumE(ll l, ll r) { return (modMul(sumCons(r), 2) - modMul(sumCons(l), 2) + MOD) % MOD; }
ll sumO(ll l, ll r) { return (modMul(sumCons(r), 2) - r - (modMul(sumCons(l), 2) - l) + MOD) % MOD; }
ll f(ll x) {
    bool isO = true;
    ll oCnt = 0, eCnt = 0;
    ll pw = 1;
    ll val = 0;
    while (x > 0) {
        ll num = min(x, pw);
        if (isO) {
            val += sumO(oCnt, oCnt + num);
            val %= MOD;
            oCnt += num;
        } else {
            val += sumE(eCnt, eCnt + num);
            val %= MOD;
            eCnt += num;
        }
        val += MOD;
        val %= MOD;
        isO = !isO;
        pw *= 2;
        x -= num;
    }
    return val;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll l, r;
    cin >> l >> r;
    cout << (f(r) - f(l - 1) + MOD) % MOD << endl;
}