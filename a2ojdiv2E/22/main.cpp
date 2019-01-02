#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
ll N;
ll A[MAXN];
ll mxEl;
vector<ll> divisors[MAXN];
void sieve() {
    for (ll i = 1; i < MAXN; i++) {
        for (ll j = i; j < MAXN; j += i) {
            divisors[j].push_back(i);
        }
    }
}
ll seg[2 * MAXN];
void build() {
    for (ll i = MAXN - 1; i >= 0; i--)
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
}

void modify(ll p, ll val) {
    for (seg[p += MAXN] = val; p > 0; p >>= 1)
        seg[p >> 1] = seg[p] + seg[p ^ 1];
}

ll query(ll l, ll r) {
    ll res = 0;
    for (l += MAXN, r += MAXN; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += seg[l++];
        if (r & 1)
            res += seg[--r];
    }
    return res;
}
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
        mxEl = max(A[i], mxEl);
    }
    for (ll i = 0; i < N; i++) {
        seg[A[i] + MAXN]++;
    }
    build();
    sieve();
    ll ans = 0;
    for (ll cur = mxEl; cur >= 1; cur--) {
        vector<ll> curCnt;
        divisors[cur].push_back(MAXN);
        for (ll i = 0; i < divisors[cur].size() - 1; i++) {
            curCnt.push_back(query(divisors[cur][i], divisors[cur][i + 1]));
        }
        ll curAns = 1;
        ll curAns2 = 1;
        for (ll i = 1; i <= curCnt.size(); i++) {
            if (i == curCnt.size()) {
                curAns = (curAns * (bin_exp(i, curCnt[i - 1]) - bin_exp(i - 1, curCnt[i - 1]))) % MOD;
            } else {
                curAns = (curAns * bin_exp(i, curCnt[i - 1])) % MOD;
            }
        }
        ans += curAns;
        ans = (ans + MOD) % MOD;
    }
    cout << ans << endl;
}