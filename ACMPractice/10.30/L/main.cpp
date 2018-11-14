#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef long long ll;
const ll RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    ll operator()(ll x) const { return hash_f(x); }
};

const ll MAXN = 1e5 + 5;
const ll MAXA = 1e9 + 5;
ll N, M;
ll A[MAXN], B[MAXN];
ll get(gp_hash_table<ll, ll, chash> &ht, int x) {
    if (ht.find(x) != ht.end())
        return ht[x];
    return 0;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> N >> t;
    for (ll i = 0; i < N; i++)
        cin >> A[i];
    cin >> M >> t;
    for (ll i = 0; i < M; i++)
        cin >> B[i];
    gp_hash_table<ll, ll, chash> cnts;
    for (int i = 0; i < N; i++)
        cnts[A[i]]++;

    for (int i = 0; i < M; i++)
        cnts[B[i]]++;
    ll ans = 0;
    for (auto i : cnts) {
        ans = max(ans, i.second);
    }
    for (ll l = 1; l < MAXA; l <<= 1) {
        gp_hash_table<ll, ll, chash> modsA, modsB;
        for (ll i = 0; i < N; i++) {
            modsA[A[i] % (2 * l)]++;
        }
        for (ll i = 0; i < M; i++) {
            modsB[B[i] % (2 * l)]++;
        }
        for (auto i : modsA) {
            ans = max(ans, i.second + get(modsB, (i.first + l) % (2 * l)));
        }
        for (auto i : modsB) {
            ans = max(ans, i.second + get(modsA, (i.first + l) % (2 * l)));
        }
    }
    cout << ans << endl;
}