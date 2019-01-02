#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef long long ll;
unsigned hash_f(uint64_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
struct chash {
    ll operator()(ll x) const { return hash_f(x); }
};
ll X, K;
ll cur = 0;
gp_hash_table<ll, bool, chash> memo;
gp_hash_table<ll, vector<ll>, chash> memoDivs;
inline void inc(ll x) {
    cout << x << ' ';
    cur++;
    if (cur == 1e5) {
        exit(0);
    }
}
void rec(ll x, ll depth) {
    if (x == 1) {
        inc(1);
        return;
    }
    if (depth == K) {
        inc(x);
        return;
    }
    if (memo.find(x) != memo.end() && memo[x]) {
        for (ll i = 0; i < K - depth; i++) {
            inc(1);
        }
        inc(x);
        return;
    }
    if (memoDivs.find(x) != memoDivs.end()) {
        for (auto i : memoDivs[x]) {
            if (i * i == x)
                continue;
            rec(x / i, depth + 1);
        }
        for (int i = memoDivs[x].size() - 1; i >= 0; i--) {
            rec(memoDivs[x][i], depth + 1);
        }
        return;
    }
    vector<ll> divisors;
    divisors.push_back(x);
    bool isPrime = true;
    rec(1, depth + 1);
    for (ll i = 2; i * i <= x; i++) {
        if (x % i != 0)
            continue;
        if (i * i != x)
            rec(i, depth + 1);
        divisors.push_back(x / i);
        isPrime = false;
    }
    if (isPrime) {
        memo[x] = true;
        rec(x, depth + 1);
    } else {
        for (ll i = divisors.size() - 1; i >= 0; i--) {
            rec(divisors[i], depth + 1);
        }
        memoDivs[x] = divisors;
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> X >> K;
    rec(X, 0);
    cout << endl;
}