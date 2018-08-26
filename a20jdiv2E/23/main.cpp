#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll N;
ll MOD;
vector<ll> cur;
ll bin_exp(ll base, ll pow) {
    if (pow == 0)
        return 1;
    return bin_exp(base * base % MOD, pow / 2) * (pow % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll x) { return bin_exp(x, MOD - 2); }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    MOD = N;
    bool isPrime = true;
    for (ll i = 2; i * i <= N; i++) {
        if (N % i == 0)
            isPrime = false;
    }
    if (!isPrime && N != 4) {
        cout << "NO" << endl;
        return 0;
    }
    if (N == 4) {
        cout << "YES\n1\n3\n2\n4" << endl;
        return 0;
    }
    vector<ll> ans;
    ans.push_back(1);
    for (ll i = 1; i < N - 1; i++) {
        ans.push_back(i * mod_inv(i + 1) % MOD);
    }
    if (N != 1)
        ans.push_back(N);
    cout << "YES" << endl;
    for (auto i : ans) {
        cout << i << endl;
    }
}
