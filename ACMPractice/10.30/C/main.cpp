#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N, A[MAXN];
int cnt[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    sort(A, A + N);
    int mVal = A[0];
    for (int i = 0; i < N; i++)
        A[i] /= mVal;

    for (int i = 0; i < N; i++) {
        if ((A[i] & (A[i] - 1)) != 0) {
            cout << -1 << endl;
            return 0;
        }
    }
    int cur = 1;
    int curPow = 0;
    for (int i = 0; i < N; i++) {
        while (A[i] != cur) {
            cur *= 2;
            curPow++;
        }
        cnt[curPow]++;
    }
    int ans = 0;
    for (int i = 0;; i++) {
        if (cnt[i] == 1 && i >= curPow)
            break;
        if (cnt[i] % 2 == 1) {
            cnt[i]++;
            ans++;
        }
        cnt[i + 1] += cnt[i] / 2;
    }
    cout << ans << endl;
}