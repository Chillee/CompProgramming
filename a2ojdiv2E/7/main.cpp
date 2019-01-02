#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 22;
ll N;
ll level[MAXN];
ll same[MAXN];
bool toggle[MAXN];
ll A[(1LL << 20) + 5];
vector<ll> invs(ll l, ll r, ll lvl) {
    if (lvl == 0) {
        return {A[l]};
    }
    ll mid = (l + r) / 2;
    auto left = invs(l, mid, lvl - 1);
    auto right = invs(mid, r, lvl - 1);
    vector<ll> res;
    ll lidx = 0;
    ll ridx = 0;
    ll numInvs = 0;
    ll sameCnt = 0;
    while (lidx < left.size() && ridx < right.size()) {
        if (left[lidx] < right[ridx]) {
            res.push_back(left[lidx]);
            lidx++;
        } else if (left[lidx] > right[ridx]) {
            res.push_back(right[ridx]);
            numInvs += left.size() - lidx;
            ridx++;
        } else if (left[lidx] == right[ridx]) {
            ll curVal = left[lidx];
            ll leftCnt = 0;
            ll rightCnt = 0;
            while (lidx < left.size() && left[lidx] == curVal) {
                res.push_back(curVal);
                lidx++;
                leftCnt++;
            }
            while (ridx < right.size() && right[ridx] == curVal) {
                res.push_back(curVal);
                ridx++;
                numInvs += left.size() - lidx;
                rightCnt++;
            }
            sameCnt += leftCnt * rightCnt;
        }
    }
    for (ll i = lidx; i < left.size(); i++) {
        res.push_back(left[i]);
    }
    for (ll i = ridx; i < right.size(); i++) {
        res.push_back(right[i]);
    }

    same[lvl] += sameCnt;
    level[lvl] += numInvs;
    return res;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    for (ll i = 0; i < (1LL << N); i++) {
        cin >> A[i];
    }
    invs(0, 1 << N, N);
    ll M;
    cin >> M;
    for (ll i = 0; i < M; i++) {
        ll x;
        cin >> x;
        for (ll j = x; j >= 1; j--) {
            toggle[j] ^= 1;
        }
        ll ans = 0;
        for (ll j = 1; j <= N; j++) {
            ll levelInvs = (1LL << (N - j)) * (1LL << (j - 1)) * (1LL << (j - 1));
            if (!toggle[j]) {
                ans += level[j];
            } else {
                ans += levelInvs - level[j] - same[j];
            }
        }
        cout << ans << endl;
    }
}