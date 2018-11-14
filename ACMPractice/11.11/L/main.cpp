#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N;
int L[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        L[a]++;
        L[b + 1]--;
    }
    int cur = 0;
    int ans = -1;
    for (int i = 0; i < MAXN; i++) {
        cur += L[i];
        if (i == cur && N - i == N - cur) {
            ans = max(i, ans);
        }
    }
    cout << ans << endl;
}