#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
ll N;
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}
ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }

void rec(int from, int to, function<int(int)> f, int &i, int &p, int q, vector<array<int, 3>> &ints) {
    if (p == q)
        return;
    if (from == to) {
        ints.push_back({i, to, p});
        i = to;
        p = q;
    } else {
        int mid = (from + to) >> 1;
        rec(from, mid, f, i, p, f(mid), ints);
        rec(mid + 1, to, f, i, p, q, ints);
    }
}
void constantIntervals(int from, int to, function<int(int)> f, vector<array<int, 3>> &ints) {
    if (to <= from)
        return;
    int i = from;
    int p = f(i), q = f(to - 1);
    rec(from, to - 1, f, i, p, q, ints);
    ints.push_back({i, to, q});
}
ll smInts(ll a, ll b) {
    a %= MOD, b %= MOD;
    ll x = (b * (b - 1) % MOD) * mod_inv(2) % MOD;
    ll y = (a * (a - 1) % MOD) * mod_inv(2) % MOD;
    return (x - y + MOD) % MOD;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    ll ans = 0;
    ll i = 1;
    for (; i * i < N; i++) {
        ans += i * (N / i) % MOD;
        ans %= MOD;
    }
    vector<array<int, 3>> inters;
    constantIntervals(
        i, N + 1, [](ll v) { return N / v; }, inters);
    for (auto i : inters) {
        ans += smInts(i[0], i[1]) * i[2] % MOD;
        ans %= MOD;
    }
    cout << ans << endl;
}