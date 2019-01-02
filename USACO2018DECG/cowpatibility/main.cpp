#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef long long ll;
uint64_t hash_f(uint64_t key) {
    key ^= key >> 33;
    key *= 0xff51afd7ed558ccd;
    key ^= key >> 33;
    key *= 0xc4ceb9fe1a85ec53;
    key ^= key >> 33;
    return key;
}
ll hash_combine(ll a, ll b) { return a * 31 + b; }
struct chash {
    ll operator()(vector<ll> x) const {
        ll cur = 1;
        for (auto i : x) {
            cur = hash_combine(cur, hash_f(i));
        }
        return cur;
    }
};
gp_hash_table<vector<ll>, ll, chash> cnt;

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
            cnt[vals]++;
        }
    }
    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        for (ll m = 0; m < (1 << 5); m++) {
            vector<ll> vals;
            for (ll j = 0; j < 5; j++) {
                if (m & (1 << j))
                    vals.push_back(A[i][j]);
            }
            ll t = cnt[vals] - 1;
            if (vals.size() % 2 != 0) {
                t *= -1;
            }
            ans += t;
        }
    }
    cout << ans / 2 << endl;
}