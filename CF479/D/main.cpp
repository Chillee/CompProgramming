#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 105;
ll N;
ll A[MAXN];
vector<ll> counts[1000];

int main() {
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    ll mxCnt = 0;
    for (ll i = 0; i < N; i++) {
        ll cnt = 0;
        ll cur = A[i];
        while (cur % 3 == 0) {
            cnt++;
            cur /= 3;
        }
        mxCnt = max(mxCnt, cnt);
        counts[cnt].push_back(A[i]);
    }
    vector<ll> results;
    for (ll i = mxCnt; i >= 0; i--) {
        if (results.size() == N) {
            break;
        }
        sort(counts[i].begin(), counts[i].end());
        for (auto j : counts[i]) {
            results.push_back(j);
        }
    }
    for (auto i : results) {
        cout << i << ' ';
    }
    cout << endl;
}