#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>     // Including tree_order_statistics_node_updat

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const ll MAXN = 1e6 + 5;
ll N;
ll A[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    ordered_set lset;
    ordered_set rset;
    for (ll i = 1; i < N; i++) {
        rset.insert(A[i]);
    }
    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        ll leftCnt = lset.size() - lset.order_of_key(A[i] + 1);
        ll rightCnt = rset.order_of_key(A[i]);
        ans += leftCnt * rightCnt;
        lset.insert(A[i]);
        rset.erase(A[i + 1]);
    }
    cout << ans << endl;
}