#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e5 + 5;
ll N, K, L;
vector<ll> staves;
bool used[MAXN];
vector<ll> results[MAXN];
int main() {
    cin >> N >> K >> L;
    for (ll i = 0; i < N * K; i++) {
        ll t;
        cin >> t;
        staves.push_back(t);
    }
    sort(staves.begin(), staves.end());
    ll limitIdx = staves.size() - 1;
    for (ll i = 0; i < staves.size(); i++) {
        if (staves[i] - staves[0] > L) {
            limitIdx = i - 1;
            break;
        }
    }
    ll curBucket = N - 1;
    while (true) {
        if (staves[curBucket * K] - staves[0] > L) {
            if (limitIdx <= 0 || curBucket == 0) {
                cout << 0 << endl;
                return 0;
            }
            swap(staves[limitIdx], staves[curBucket * K]);
            curBucket--;
            limitIdx--;
        } else {
            break;
        }
    }
    for (ll i = 0; i < staves.size(); i++) {
        results[i / K].push_back(i);
    }
    vector<ll> mins;
    for (ll i = 0; i < N; i++) {
        ll curMn = 1e9 + 9;
        for (auto j : results[i]) {
            curMn = min(staves[j], curMn);
        }
        mins.push_back(curMn);
    }
    sort(mins.begin(), mins.end());
    if (abs(mins[0] - mins[mins.size() - 1]) > L) {
        cout << 0 << endl;
        return 0;
    }

    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        ll cur = 1e9 + 9;
        for (ll j : results[i]) {
            cur = min(staves[j], cur);
        }
        ans += cur;
    }
    cout << ans << endl;
}