#include <bits/stdc++.h>

using namespace std;

int N, R;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> R;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        if (t >= R)
            cout << "Good boi" << endl;
        else
            cout << "Bad boi" << endl;
    }
}