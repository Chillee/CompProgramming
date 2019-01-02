#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const ll MAXN = 2e5 + 5;
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
ll N;
ll A[MAXN];
ll sm = 0;
ll rem = 0;
ll sufSum[MAXN], prfSum[MAXN], prfCnt[MAXN];
ll fac[MAXN];
int seg[2 * MAXN];
int segN;
void build() {
    for (int i = segN - 1; i >= 0; i--)
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
}

void modify(int p, int val) {
    for (seg[p += segN] = val; p > 0; p >>= 1)
        seg[p >> 1] = seg[p] + seg[p ^ 1];
}

int query(int l, int r) {
    int res = 0;
    for (l += segN, r += segN; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += seg[l++];
        if (r & 1)
            res += seg[--r];
    }
    return res;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = 1;
    for (ll i = 1; i < MAXN; i++)
        fac[i] = (fac[i - 1] * i) % MOD;
    cin >> N;
    segN = N + 1;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
        if (A[i] == -1)
            rem++;
    }
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] != -1) {
            ans += query(A[i], N + 1);
            modify(A[i], 1);
            ans %= MOD;
        }
    }
    // cout << query(0, 4) << endl;
    ans *= fac[rem];
    ans %= MOD;
    ll sm = 0;
    for (ll i = 0; i < N; i++) {
        prfSum[i] = sm;
        if (A[i] != -1)
            sm += A[i] - 1 - query(0, A[i]);
        sm %= MOD;
    }
    sm = 0;
    for (ll i = N - 1; i >= 0; i--) {
        sufSum[i] = sm;
        if (A[i] != -1) {
            sm += N - A[i] - query(A[i] + 1, N + 1);
        }
        sm %= MOD;
    }

    for (ll i = 0; i < N; i++) {
        if (A[i] != -1)
            continue;
        ans += (sufSum[i] * fac[rem - 1]) % MOD;
        ans %= MOD;
        ans += prfSum[i] * fac[rem - 1];
        ans %= MOD;
    }
    ll res = rem * (rem - 1);
    res %= MOD;
    res *= mod_inv(4);
    res %= MOD;
    res *= fac[rem];
    res %= MOD;
    ans += res;
    ans %= MOD;
    // cout << ans << endl;
    cout << (ans * mod_inv(fac[rem])) % MOD << endl;
}