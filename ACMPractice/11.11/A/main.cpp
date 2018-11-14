#include <bits/stdc++.h>

using namespace std;

int K;
string A, B;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> K;
    cin >> A >> B;
    int match = 0, nmatch = 0;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] == B[i])
            match++;
        else
            nmatch++;
    }
    if (K <= match)
        cout << K + nmatch << endl;
    else
        cout << A.size() + match - K << endl;
}