#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 2e5 + 5;
ll N;
ll W[MAXN], H[MAXN], C[MAXN];
ll lcm(ll a, ll b) { return a * b / __gcd(a, b); }
int main() {
    cin >> N;
    ll minC = 1LL << 60;
    for (ll i = 0; i < N; i++) {
        cin >> W[i] >> H[i] >> C[i];
        minC = min(minC, C[i]);
    }
    ll curLcm = W[0];
    for (ll i = 1; i < N; i++) {
        curLcm = lcm(curLcm, W[i]);
        cout << curLcm << endl;
    }
    for (ll i = 0; i < N; i++) {
        if ((C[i] * W[i]) % curLcm != 0) {
            cout << 0 << endl;
            // return 0;
        }
        C[i] = C[i] * W[i] / curLcm;
    }
    ll curGcd = C[0];
    for (ll i = 0; i < N; i++) {
        curGcd = __gcd(curGcd, C[i]);
    }
    cout << curGcd << endl;
    ll ans = 0;
    for (ll i = 1; i * i <= curGcd; i++) {
        if (i * i == curGcd && curGcd % i == 0) {
            ans++;
        } else if (curGcd % i == 0) {
            ans += 2;
        }
    }
    cout << ans << endl;
}