#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll N;
set<ll> vals;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    vector<ll> divs;
    for (int i = 1; i * i <= N; i++) {
        if (N % i == 0) {
            divs.push_back(i);
            divs.push_back(N / i);
        }
    }
    for (auto i : divs) {
        ll gcd = __gcd(i, N);
        ll cnt = N / gcd - 1;
        ll sm = gcd * cnt * (cnt + 1) / 2;
        sm += cnt + 1;
        vals.insert(sm);
    }
    for (auto i : vals)
        cout << i << ' ';
    cout << endl;
}