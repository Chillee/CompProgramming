#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>
    ordered_set; // order_of_key, find_by_order

const int MAXN = 2e5 + 5;
int K, N;
int A[MAXN];
ordered_set meds;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    for (int i = 0; i < K; i++)
        meds.insert({A[i], i});
    for (int i = K; i <= N; i++) {
        if (K & 1)
            cout << meds.find_by_order(K / 2)->first << ' ';
        else
            cout << min(meds.find_by_order(K / 2)->first, meds.find_by_order(K / 2 - 1)->first) << ' ';
        meds.insert({A[i], i});
        meds.erase({A[i - K], i - K});
    }
    cout << endl;
}