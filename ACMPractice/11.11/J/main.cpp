#include <bits/stdc++.h>

using namespace std;

int N, S;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> S;
    int sm = 0;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        sm = max(sm, t);
    }
    sm *= S;
    cout << (sm + 999) / 1000 << endl;
}