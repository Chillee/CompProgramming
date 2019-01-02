#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
const ll MAXN = 3e5 + 5;
ll N;
ll P[MAXN];
char C[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> P[i] >> C[i];
    }
    ll res = 0;
    vector<ll> reds, blues;
    ll i = 0;
    while (i < N && C[i] != 'G') {
        if (C[i] == 'R')
            reds.push_back(P[i]);
        else if (C[i] == 'B')
            blues.push_back(P[i]);
        i++;
    }
    if (!reds.empty())
        res += *reds.rbegin() - *reds.begin();
    if (!blues.empty())
        res += *blues.rbegin() - *blues.begin();
    if (i == N) {
        cout << res << endl;
        return 0;
    }
    if (!reds.empty())
        res += P[i] - *reds.rbegin();
    if (!blues.empty())
        res += P[i] - *blues.rbegin();
    while (true) {
        ll nextP = i + 1;
        while (nextP < N && C[nextP] != 'G')
            nextP++;
        if (nextP == N)
            break;
        vector<ll> reds;
        vector<ll> blues;
        for (ll j = i; j <= nextP; j++) {
            if (C[j] == 'R')
                reds.push_back(P[j]);
            else if (C[j] == 'B')
                blues.push_back(P[j]);
            else {
                reds.push_back(P[j]);
                blues.push_back(P[j]);
            }
        }
        ll rSum = 0;
        ll maxRedge = 0;
        for (ll j = 0; j < reds.size() - 1; j++) {
            ll d = reds[j + 1] - reds[j];
            rSum += d;
            maxRedge = max(maxRedge, d);
        }
        ll bSum = 0;
        ll maxBedge = 0;
        for (ll j = 0; j < blues.size() - 1; j++) {
            ll d = blues[j + 1] - blues[j];
            bSum += d;
            maxBedge = max(maxBedge, d);
        }
        res += min(rSum + bSum, rSum - maxRedge + bSum - maxBedge + P[nextP] - P[i]);
        i = nextP;
    }
    reds.clear(), blues.clear();
    ll maxRed = P[i];
    ll maxBlue = P[i];
    for (ll j = i; j < N; j++) {
        if (C[j] == 'R')
            maxRed = P[j];
        else if (C[j] == 'B')
            maxBlue = P[j];
    }
    res += (maxRed - P[i]) + (maxBlue - P[i]);
    cout << res << endl;
}
