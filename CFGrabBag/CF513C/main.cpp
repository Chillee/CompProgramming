#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2005;
ll N, M, X;
ll A[MAXN], B[MAXN];
ll prefA[MAXN], prefB[MAXN];
ll dpA[MAXN], dpB[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (ll i = 0; i < N; i++)
        cin >> A[i];
    for (ll i = 0; i < M; i++)
        cin >> B[i];
    cin >> X;
    partial_sum(A, A + N, prefA + 1);
    partial_sum(B, B + M, prefB + 1);
    for (ll j = 1; j <= N; j++) {
        dpA[j] = 1e9 + 5;
        for (ll i = 0; i <= N - j; i++)
            dpA[j] = min(dpA[j], prefA[i + j] - prefA[i]);
    }
    for (ll j = 1; j <= M; j++) {
        dpB[j] = 1e9 + 5;
        for (ll i = 0; i <= M - j; i++)
            dpB[j] = min(dpB[j], prefB[i + j] - prefB[i]);
    }
    ll ans = 0;
    for (ll i = 1; i <= N; i++) {
        for (ll j = 1; j <= M; j++) {
            if (dpA[i] * dpB[j] <= X)
                ans = max(ans, i * j);
        }
    }
    cout << ans << endl;
}