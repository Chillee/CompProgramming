#include <bits/stdc++.h>

using namespace std;

const int MAXN = 370;
int N;
bool pushes[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    int cnt = 0;
    int cur = 0;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        pushes[t] = true;
    }
    for (int i = 1; i <= 365; i++) {
        if (pushes[i]) {
            cnt += 1;
        }
        cur += cnt;
        if (cur >= 20) {
            ans++;
            cnt = 0, cur = 0;
        }
    }
    if (cur > 0) {
        ans++;
    }
    cout << ans << endl;
}