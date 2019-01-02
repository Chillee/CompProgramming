#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
ll N;
ll B[MAXN];
ll res[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N / 2; i++) {
        cin >> B[i];
    }
    ll curMx = 1e18 + 5;
    ll curMn = 0;
    for (ll i = 0; i < N / 2; i++) {
        res[N - i - 1] = min(curMx, B[i] - curMn);
        res[i] = B[i] - res[N - i - 1];
        curMx = min(curMx, res[N - i - 1]);
        curMn = max(curMn, res[i]);
    }
    for (ll i = 0; i < N; i++)
        cout << res[i] << ' ';
    cout << endl;
}