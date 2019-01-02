#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e5 + 5;
ll N;
ll A[MAXN];
ll countRev[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    set<ll> cur;
    for (ll i = N - 1; i >= 0; i--) {
        countRev[i] = cur.size();
        cur.insert(A[i]);
    }
    cur.clear();
    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        if (cur.find(A[i]) == cur.end()) {
            // cout << i << ' ' << countRev[i] << endl;
            ans += countRev[i];
        }
        cur.insert(A[i]);
    }
    cout << ans << endl;
}