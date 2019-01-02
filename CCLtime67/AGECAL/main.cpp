#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 5;
int T, N;
int A[MAXN];
int sm[MAXN];
array<int, 3> birth;
array<int, 3> cur;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> A[i];
            sm[i + 1] = sm[i] + A[i];
        }
        cin >> birth[0] >> birth[1] >> birth[2] >> cur[0] >> cur[1] >> cur[2];
        birth[1]--, birth[2]--, cur[1]--, cur[2]--;
        int ans = 0;
        ans -= birth[2];
        birth[2] = 0;
        ans -= sm[birth[1]];
        birth[1] = 0;
        for (; birth[0] < cur[0]; birth[0]++) {
            ans += sm[N];
            if (birth[0] % 4 == 0)
                ans++;
        }
        for (; birth[1] < cur[1]; birth[1]++) {
            ans += A[birth[1]];
        }
        ans += cur[2];
        cout << ans + 1 << endl;
    }
}