#include <bits/stdc++.h>

using namespace std;

int tests, N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> tests;
    for (int t = 0; t < tests; t++) {
        cin >> N;
        string S, T;
        cin >> S >> T;
        int fst = -1, prevt = -1;
        bool foundSol = true;
        for (int i = 0; i < N; i++) {
            if (S[i] == T[i])
                continue;
            if (fst == -1)
                fst = S[i];
            if (prevt != -1 && S[i] != prevt) {
                cout << "NO" << endl;
                foundSol = false;
                break;
            }
            prevt = T[i];
        }
        if (foundSol)
            cout << (fst == prevt ? "YES" : "NO") << endl;
    }
}