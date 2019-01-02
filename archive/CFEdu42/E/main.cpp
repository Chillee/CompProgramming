#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 2e5 + 5;
ll N;
ll X[MAXN];
char C[MAXN];
int main() {
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> X[i] >> C[i];
    }
    ll res = 0;
    set<ll> reds;
    set<ll> blues;
    ll i = 0;
    while (i < N && C[i] != 'P') {
        if (C[i] == 'R')
            reds.insert(X[i]);
        if (C[i] == 'B')
            blues.insert(X[i]);
        i++;
    }
    if (!reds.empty())
        res += abs(*reds.begin() - *reds.rbegin());
    if (!blues.empty())
        res += abs(*blues.begin() - *blues.rbegin());
    if (i == N) {
        cout << res << endl;
        return 0;
    }
    if (!reds.empty())
        res += abs(X[i] - *reds.rbegin());
    if (!blues.empty())
        res += abs(X[i] - *blues.rbegin());
    while (true) {
        // cout << i << ' ' << res << endl;
        ll nextP = i + 1;
        while (nextP < N && C[nextP] != 'P') {
            nextP++;
        }
        if (nextP == N) {
            break;
        }
        vector<ll> reds;
        vector<ll> blues;
        for (ll j = i; j <= nextP; j++) {
            if (C[j] == 'R') {
                reds.push_back(X[j]);
            } else if (C[j] == 'B') {
                blues.push_back(X[j]);
            }
            if (C[j] == 'P') {
                reds.push_back(X[j]);
                blues.push_back(X[j]);
            }
        }
        ll rsum = 0;
        ll minRedge = -1e18;
        for (ll j = 0; j < reds.size() - 1; j++) {
            rsum += abs(reds[j] - reds[j + 1]);
            minRedge = max(minRedge, abs(reds[j] - reds[j + 1]));
        }
        ll bsum = 0;
        ll minBedge = -1e18;
        for (ll j = 0; j < blues.size() - 1; j++) {
            bsum += abs(blues[j] - blues[j + 1]);
            minBedge = max(minBedge, abs(blues[j] - blues[j + 1]));
        }
        if (blues.size() == 2 && reds.size() == 2) {
            res += abs(X[nextP] - X[i]);
        } else {

            res += min(rsum + bsum, rsum - minRedge + bsum - minBedge + abs(X[nextP] - X[i]));
        }

        i = nextP;
    }
    reds.clear();
    blues.clear();
    ll origP = i;
    while (i < N) {
        if (C[i] == 'R')
            reds.insert(X[i]);
        if (C[i] == 'B')
            blues.insert(X[i]);
        i++;
    }
    if (!reds.empty()) {
        res += abs(*reds.begin() - *reds.rbegin());
        res += abs(X[origP] - *reds.begin());
    }

    if (!blues.empty()) {
        res += abs(*blues.begin() - *blues.rbegin());
        res += abs(X[origP] - *blues.begin());
    }
    cout << res << endl;
}