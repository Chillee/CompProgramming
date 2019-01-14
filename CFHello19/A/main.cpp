#include <bits/stdc++.h>

using namespace std;

string S;
string A[5];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    for (int i = 0; i < 5; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < 5; i++) {
        if (A[i][0] == S[0] || A[i][1] == S[1]) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
}