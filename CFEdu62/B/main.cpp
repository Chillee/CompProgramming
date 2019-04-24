#include <bits/stdc++.h>

using namespace std;

int T, N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        string S;
        cin >> S;
        int ans = 1e9 + 5;
        for (int i = 0; i < S.size(); i++) {
            if (S[i] == '>')
                ans = min(ans, i);
            if (S[S.size() - 1 - i] == '<')
                ans = min(ans, i);
        }
        cout << ans << endl;
    }
}