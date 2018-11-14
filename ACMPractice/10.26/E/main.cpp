#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

string S;
string T;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S >> T;
    int start = -1, end = -1;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] != T[i]) {
            start = i;
            break;
        }
    }
    for (int i = S.size() - 1; i >= 0; i--) {
        if (S[i] != T[i]) {
            end = i;
            break;
        }
    }
    if (start == -1 || end == -1) {
        cout << "YES" << endl;
        return 0;
    }
    for (int i = 0; i <= end - start; i++) {
        if (S[start + i] != T[end - i]) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
}