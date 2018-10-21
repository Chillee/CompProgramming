#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

int T, N, M;
signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N >> M;
        int ans = 0;
        for (int i = 0; i < N; i++) {
            int startHour, startMinute, endHour, endMinute;
            scanf("%d:%d %d:%d", &startHour, &startMinute, &endHour, &endMinute);
            ans += (endHour - startHour) * 60 + (endMinute - startMinute);
        }
        if (ans / 60 >= M) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}