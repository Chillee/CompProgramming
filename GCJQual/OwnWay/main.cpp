#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;
        string S;
        cin >> S;
        string ans;
        int r = 1, c = 1;
        for (int i = 0; i < 2 * N - 2; i++) {
            char attempt;
            if (r < c)
                attempt = 'S';
            else
                attempt = 'E';
            if (attempt == 'S' && S[i] == 'S')
                attempt = 'E';
            else if (attempt == 'E' && S[i] == 'E')
                attempt = 'S';
            if (attempt == 'S')
                r++;
            else
                c++;

            ans.push_back(attempt);
        }
        cout << "Case #" << t + 1 << ": " << ans << endl;
    }
}