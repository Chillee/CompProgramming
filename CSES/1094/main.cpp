#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;
int N;
int A[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    long long ans = 0;
    for (int i = 1; i < N; i++) {
        ans += max(A[i - 1] - A[i], 0);
        A[i] = max(A[i - 1], A[i]);
    }
    cout << ans << endl;
}