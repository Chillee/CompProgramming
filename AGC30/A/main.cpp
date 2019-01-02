#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll A, B, C;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> A >> B >> C;
    cout << min(A + B + 1, C) + B << endl;
}