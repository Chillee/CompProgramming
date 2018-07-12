#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
string S, T;
ll back[MAXN];
ll dp[MAXN];
void kmpPreprocess(string P) {
    ll j = -1;
    back[0] = -1;
    for (ll i = 0; i < P.size(); i++) {
        while (j >= 0 && P[i] != P[j]) {
            j = back[j];
        }
        j++;
        back[i + 1] = j;
    }
}
vector<ll> kmpSearch(string S, string P) {
    vector<ll> res;
    ll j = 0;
    for (ll i = 0; i < S.size(); i++) {
        while (j >= 0 && S[i] != P[j]) {
            j = back[j];
        }
        j++;
        if (j == P.size()) {
            res.push_back(i);
            j = back[j];
        }
    }
    return res;
}

ll vals[MAXN];
ll sums[MAXN];
ll sums2[MAXN];
bool isGood[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S >> T;
    kmpPreprocess(T);
    auto positions = kmpSearch(S, T);
    if (positions.size() == 0) {
        cout << 0 << endl;
        return 0;
    }
    for (auto i : positions) {
        isGood[i] = true;
    }
    if (isGood[0]) {
        vals[0] = 1;
        sums[0] = 1;
        sums2[0] = 1;
    }
    for (ll i = 1; i < S.size(); i++) {
        if (!isGood[i]) {
            vals[i] = vals[i - 1];
        } else {
            vals[i] = (sums2[i - T.size()] + (i - T.size() + 2)) % MOD;
        }
        sums[i] = (sums[i - 1] + vals[i]) % MOD;
        sums2[i] = (sums2[i - 1] + sums[i]) % MOD;
    }
    ll res = 0;
    for (ll i = 0; i < S.size(); i++) {
        res = (res + vals[i]) % MOD;
    }
    cout << res << endl;
}