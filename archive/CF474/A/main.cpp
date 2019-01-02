#include <bits/stdc++.h>

using namespace std;

string S;
int aCnt, bCnt, cCnt = 0;
int main() {
    cin >> S;
    char curChar = 'a';
    for (int i = 0; i < S.length(); i++) {
        if (S[i] != curChar && S[i] != curChar + 1) {
            cout << "NO" << endl;
            return 0;
        } else if (S[i] != curChar && S[i] == curChar + 1) {
            curChar = S[i];
        }
    }
    for (auto i : S) {
        if (i == 'a') {
            aCnt++;
        } else if (i == 'b') {
            bCnt++;
        } else if (i == 'c') {
            cCnt++;
        }
    }
    if (aCnt == 0 || bCnt == 0 || cCnt == 0 || (cCnt != aCnt && cCnt != bCnt)) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
}