#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 2e5 + 5;
int N;
int cnt[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        cnt[t] += 1;
    }
    int ans = 0;
    for (int i = 0; i < MAXN; i++) {
        ans += cnt[i] / 2;
    }
    cout << ans / 2 << endl;
}