#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 55;

ll N;
ll P[MAXN];
vector<ll> prizes;
vector<ll> ans;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> P[i];
    }
    for (ll i = 0; i < 5; i++) {
        ll t;
        cin >> t;
        prizes.push_back(t);
        ans.push_back(0);
    }
    ll curPts = 0;
    for (ll i = 0; i < N; i++) {
        curPts += P[i];
        for (ll j = 4; j >= 0; j--) {
            ll numRemoved = curPts / prizes[j];
            ans[j] += numRemoved;
            curPts -= numRemoved * prizes[j];
        }
    }
    for (ll i = 0; i < 5; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    cout << curPts << endl;
}