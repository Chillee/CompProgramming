#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

int N;

vector<int> denoms;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        string t;
        cin >> t;
        if (t[0] == '1') {
            cout << 1 << endl;
        } else if (t.size() <= 2) {
            cout << 1 << endl;
        } else {
            int cur = stoi(t.substr(2, t.size() - 2), 0);
            for (int j = 0; j < 4 - (t.size() - 2); j++) {
                cur *= 10;
            }
            cout << 10000 / __gcd(cur, 10000) << endl;
        }
    }
}