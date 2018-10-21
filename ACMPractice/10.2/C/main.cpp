#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
typedef long long ll;
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
    ordered_set; // order_of_key, find_by_order

const ll RANDOM =
    (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
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
ll T, N;
ll A[MAXN], B[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (ll t = 0; t < T; t++) {
        cin >> N;
        gp_hash_table<ll, ll, chash> mapping;
        for (ll i = 0; i < N; i++) {
            cin >> A[i];
            mapping[A[i]] = i;
        }
        for (ll i = 0; i < N; i++) {
            cin >> B[i];
        }
        ll ans = 0;
        ordered_set cur;
        for (ll i = 0; i < N; i++) {
            ans += cur.size() - cur.order_of_key(mapping[B[i]]);
            cur.insert(mapping[B[i]]);
        }
        cout << ans << endl;
    }
}