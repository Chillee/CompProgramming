#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 1e6 + 5;
const int MOD = 1e9 + 7;
int N;
ll fac[MAXN], ifac[MAXN];
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
ll nCr(int n, int r) {
    int num = fac[n];
    int denom = (fac[r] * fac[n - r]) % MOD;
    return num * mod_inv(denom) % MOD;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
        ifac[i] = mod_inv(fac[i]);
    }
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        cout << nCr(a, b) << endl;
    }
}