#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
multiset<ll> low, high;
ll lSum, rSum;
ll N, K;
ll A[MAXN];
ll getOutput() {
    ll md = *low.rbegin();
    return rSum - high.size() * md + low.size() * md - lSum;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (ll i = 0; i < N; i++)
        cin >> A[i];
    vector<ll> vals;
    for (ll i = 0; i < K; i++)
        vals.push_back(A[i]);
    sort(vals.begin(), vals.end());
    for (ll i = 0; i < (K + 1) / 2; i++) {
        low.insert(vals[i]);
        lSum += vals[i];
    }
    for (ll i = (K + 1) / 2; i < K; i++)
        high.insert(vals[i]), rSum += vals[i];
    cout << getOutput() << ' ';
    for (ll i = K; i < N; i++) {
        if (A[i] > *low.rbegin())
            high.insert(A[i]), rSum += A[i];
        else
            low.insert(A[i]), lSum += A[i];
        if (*low.rbegin() >= A[i - K]) {
            low.erase(low.find(A[i - K])), lSum -= A[i - K];
        } else {
            high.erase(high.find(A[i - K])), rSum -= A[i - K];
        }
        // cout << lSum << ' ' << rSum << endl;
        if (high.size() > low.size()) {
            low.insert(*high.begin()), lSum += *high.begin();
            rSum -= *high.begin(), high.erase(high.begin());
        } else if (low.size() > high.size() + 1) {
            high.insert(*low.rbegin()), rSum += *low.rbegin();
            lSum -= *low.rbegin(), low.erase(--low.end());
        }
        // cout << lSum << ' ' << rSum << endl;
        // cout << endl;
        cout << getOutput() << ' ';
    }
    cout << endl;
}