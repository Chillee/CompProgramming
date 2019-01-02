#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef long long ll;
// const ll RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
ll chash(ll x) { return hash_f(x); }
gp_hash_table<ll, ll> cnt;

ll hashv(vector<ll> &x) {
    ll cur = 1;
    for (auto i : x) {
        cur = hash_combine(cur, chash(i));
    }
    return cur;
}
const ll MAXN = 5e4 + 5;
ll N;
ll A[MAXN][5];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("cowpatibility.in", "r", stdin);
    // freopen("cowpatibility.out", "w", stdout);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < 5; j++) {
            cin >> A[i][j];
        }
        sort(begin(A[i]), end(A[i]));
    }
    for (ll i = 0; i < N; i++) {
        for (ll m = 0; m < (1 << 5); m++) {
            vector<ll> vals;
            for (ll j = 0; j < 5; j++) {
                if (m & (1 << j))
                    vals.push_back(A[i][j]);
            }
            cnt[hashv(vals)]++;
        }
    }
    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < N; j++) {
            if (i == j)
                continue;
            bool found = false;
            for (int k = 0; k < 5; k++)
                for (int l = 0; l < 5; l++) {
                    if (A[i][k] == A[j][l]) {
                        found = true;
                        break;
                    }
                }
            if (!found)
                ans++;
        }
        // for (ll m = 0; m < (1 << 5); m++) {
        //     vector<ll> vals;
        //     for (ll j = 0; j < 5; j++) {
        //         if (m & (1 << j))
        //             vals.push_back(A[i][j]);
        //     }
        //     ll t = cnt[hashv(vals)] - 1;
        //     if (vals.size() % 2 != 0) {
        //         t *= -1;
        //     }
        //     ans += t;
        // }
    }
    vector<ll> t = {4, 5};
    // cout << cnt[hashv(t)] << endl;
    cout << ans / 2 << endl;
}