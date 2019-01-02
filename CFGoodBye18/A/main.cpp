#include <bits/stdc++.h>

using namespace std;

int Y, B, R;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> Y >> B >> R;
    B--, R -= 2;
    cout << min(min(Y, B), R) * 3 + 3 << endl;
}