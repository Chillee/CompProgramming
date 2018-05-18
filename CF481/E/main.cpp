#include <bits/stdc++.h>

using namespace std;

int N, W;
int main() {

    cin >> N >> W;
    int mx, mn, cur;
    mx = 0;
    mn = 0;
    cur = 0;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        cur += t;
        mx = max(mx, cur);
        mn = min(mn, cur);
    }
    int res = W + 1 - mx + mn;
    if (res > 0) {
        cout << res << endl;
    } else {
        cout << 0 << endl;
    }
}