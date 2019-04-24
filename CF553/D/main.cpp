#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

const ll MAXN = 1e5 + 5;
ll N;
array<ll, 2> students[MAXN];
bool cmp(array<ll, 2> a, array<ll, 2> b) { return b[0] + a[1] < a[0] + b[1]; }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++)
        cin >> students[i][0] >> students[i][1];
    sort(students, students + N, cmp);
    ll ans = 0;
    ll cnt = 0;
    for (ll i = 0; i < N; i++) {
        ans += students[i][0] * cnt;
        ans += students[N - i - 1][1] * cnt;
        cnt++;
    }
    cout << ans << endl;
}