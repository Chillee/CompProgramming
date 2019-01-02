#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

int N;
string S;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    cin >> S;
    char cur = '0';
    int ans = 0;
    for (int i = S.size() - 1; i >= 0; i--) {
        if (cur != S[i]) {
            ans++;
            cur = S[i];
        }
    }
    cout << ans << endl;
}