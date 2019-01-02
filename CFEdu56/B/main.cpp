#include <bits/stdc++.h>

using namespace std;

int cnts[26];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    string S;
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> S;
        fill(begin(cnts), end(cnts), 0);
        string res;
        for (int i = 0; i < S.size(); i++) {
            cnts[S[i] - 'a']++;
        }

        int numOdd = 0;
        for (int i = 0; i < 26; i++) {
            if (cnts[i] > 0) {
                numOdd++;
            }
        }
        if (numOdd == 1) {
            cout << -1 << endl;
        } else {
            for (int i = 0; i < 26; i++) {
                res += string(cnts[i], i + 'a');
            }
            cout << res << endl;
        }
    }
}