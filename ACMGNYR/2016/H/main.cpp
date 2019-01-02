#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
int P, K, N;
array<int, 2> A[MAXN];
int orig[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P;
    for (int p = 0; p < P; p++) {
        cin >> K >> N;
        for (int i = 0; i < N; i++) {
            int t;
            cin >> t;
            A[i] = {t, i};
            orig[i] = t;
        }
        vector<int> vals(N);
        sort(A, A + N);
        for (int i = 0; i < N; i++) {
            vals[A[i][1]] = i;
        }
        int ans = 0;
        int cur = 0;
        for (int i = 0; i < N; i++) {
            // cout << i << ' ' << vals[i] << ' ' << A[cur][0] << endl;
            if (vals[i] == cur || orig[i] == A[cur][0]) {
                ans++;
                cur++;
            }
        }
        cout << K << ' ' << N - ans << endl;
    }
}