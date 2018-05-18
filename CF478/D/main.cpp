#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 200005;
ll N, A, B;
map<ll, ll> cnts;
map<pair<ll, ll>, ll> slope;
ll X[MAXN], VX[MAXN], VY[MAXN];

int main() {
    cin >> N >> A >> B;
    ll res = 0;
    for (ll i = 0; i < N; i++) {
        cin >> X[i] >> VX[i] >> VY[i];
        ll val = VY[i] - A * VX[i];
        res += cnts[val] - slope[{VX[i], VY[i]}];
        cnts[val]++;
        slope[{VX[i], VY[i]}]++;
    }

    cout << res * 2 << endl;
}