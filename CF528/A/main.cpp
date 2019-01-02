#include <bits/stdc++.h>

using namespace std;

string S, T;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    if (S.size() == 1) {
        cout << S << endl;
        return 0;
    }
    int idx = (S.size() - 1) / 2;
    for (int i = 0; i + idx < S.size();) {
        if (i != 0)
            T.push_back(S[idx + i]);
        if (idx - i >= 0)
            T.push_back(S[idx - i]);
        i++;
    }
    cout << T << endl;
}