#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 5;
int T;
int N, M, K;
bool isSmall[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N >> M >> K;
        for (int i = 0; i < N; i++) {
            string t;
            cin >> t;
            isSmall[i] = (t == "S");
        }
        int mxTest = K;
        int ans = 0;
        for (int i = 0; i < M; i++) {
            char t;
            int cur;
            cin >> t;
            if (t == 'A') {
                mxTest = 1e5;
                continue;
            }
            cin >> cur;
            cur--;
            if (t == 'W' && isSmall[cur] && cur <= mxTest) {
                ans++;
            }
            mxTest = max(cur, mxTest);
        }
        cout << ans << endl;
    }
}