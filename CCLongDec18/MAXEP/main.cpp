#include <bits/stdc++.h>

using namespace std;

void fail() {
    cout << "3 12345" << endl;
    exit(0);
}
int N, C;
int cur = 1000;
bool query(int x) {
    cur--;
    cout << 1 << ' ' << x << endl;
    int t;
    cin >> t;
    if (t == -1)
        fail();
    return t == 1;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int d;
    cin >> N >> C;
    int l = 1, r = N;
    while (true) {
        assert(cur != 0);
        d = (((r - l) * 2 + C) / cur) + 1;
        if (d <= 0)
            fail();
        bool good = true;
        for (int i = l; i <= r; i += d) {
            bool res = query(i);
            if (!res) {
                l = i;
            } else {
                r = i;
                cout << 2 << endl;
                cur -= C;
                good = false;
                break;
            }
        }
        if (!good)
            break;
    }
    for (int i = l; i <= r; i++) {
        if (query(i)) {
            cout << 3 << ' ' << i << endl;
            exit(0);
        }
    }
}