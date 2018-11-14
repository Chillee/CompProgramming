#include <bits/stdc++.h>

using namespace std;

int Ca, Ba, Pa, Cr, Br, Pr;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> Ca >> Ba >> Pa;
    cin >> Cr >> Br >> Pr;
    int ans = max(Cr - Ca, 0) + max(Br - Ba, 0) + max(Pr - Pa, 0);
    cout << ans << endl;
}