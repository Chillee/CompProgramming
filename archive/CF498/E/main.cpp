#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e6 + 5;
const ll MOD = 998244353;

ll N;
ll A[MAXN];
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    ll totSum = 0;
    ll curSum = 0;
    for (ll i = 0; i < N - 1; i++) {
        curSum = (curSum + A[i] * bin_exp(2, N - i - 2)) % MOD;
        totSum = (totSum + curSum) % MOD;
    }
    for (ll i = 0; i < N; i++) {
        totSum = (totSum + A[i] * bin_exp(2, N - i - 1)) % MOD;
    }
    cout << totSum << endl;
}