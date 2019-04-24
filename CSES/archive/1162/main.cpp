#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; // order_of_key, find_by_order

ll N;
ll A[MAXN];
ll cur[MAXN];
vector<ll> ans;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
        A[i]--;
    }
    ll cnt = 0;
    ordered_set bb;
    for (ll i = 0; i < N; i++) {
        cnt += bb.size() - bb.order_of_key(A[i]);
        bb.insert(A[i]);
    }
    ans.push_back(cnt);
    for (ll i = 0; i < N; i++)
        cur[i] = A[i];
    cnt = 0;
    vector<ll> proc;
    for (ll i = 0; i < N; i++)
        proc.push_back(i);
    while (!proc.empty()) {
        ll i = proc.back();
        proc.pop_back();
        if (cur[i] != i) {
            swap(cur[i], cur[cur[i]]);
            proc.push_back(i);
            cnt++;
        }
    }
    ans.push_back(cnt);
    cnt = 0;
    for (ll i = 0; i < N; i++)
        cur[i] = A[i];
    vector<ll> cans;
    for (ll i = 0; i < N; i++) {
        auto it = lower_bound(cans.begin(), cans.end(), cur[i]);
        if (it == cans.end())
            cans.push_back(cur[i]);
        else
            *it = cur[i];
    }
    ans.push_back(N - cans.size());
    ll cur = N - 1;
    for (ll i = N - 1; i >= 0; i--) {
        if (A[i] == cur)
            cur--;
    }
    ans.push_back(cur + 1);
    for (auto i : ans)
        cout << i << ' ';
    cout << endl;
}