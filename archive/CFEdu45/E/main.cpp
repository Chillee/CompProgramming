#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e6 + 5;
ll N, M, K;
ll pushBack[MAXN];
ll A[MAXN];
ll S[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> K;
    for (ll i = 0; i < M; i++) {
        cin >> A[i];
    }
    for (ll i = 1; i <= K; i++) {
        cin >> S[i];
    }
    for (ll i = 0; i < M; i++) {
        pushBack[A[i]] = 1;
    }
    for (ll i = 0; i < N; i++) {
        ll cur = 1;
        while (pushBack[i] != 0) {
            pushBack[i] = cur;
            cur++;
            i++;
        }
    }
    if (pushBack[0] != 0) {
        cout << -1 << endl;
        return 0;
    }
    ll ans = 1e15;
    for (ll i = 1; i <= K; i++) {
        ll curAns = 0;
        ll curIdx = 0;
        while (curIdx < N) {
            ll oldIdx = curIdx;
            curAns += S[i];
            curIdx += i;
            if (curIdx >= N)
                break;
            curIdx -= pushBack[curIdx];
            if (curIdx <= oldIdx) {
                curAns = 1e15;
                break;
            }
        }
        ans = min(ans, curAns);
    }
    if (ans >= 1e15) {
        cout << -1 << endl;
        return 0;
    }
    cout << ans << endl;
}