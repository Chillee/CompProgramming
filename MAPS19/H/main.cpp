#include <bits/stdc++.h>

using namespace std;

string S, P;
int cnt[26];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S >> P;
    for (auto i : S) {
        cnt[i - 'A']++;
    }
    int failed = 0;
    int used = 0;
    for (auto j : P) {
        bool found = false;
        for (auto i : S) {
            if (i == j) {
                found = true;
                used++;
            }
        }
        if (!found) {
            failed++;
        }
        if (used == S.size()) {
            cout << "WIN" << endl;
            return 0;
        }
        if (failed == 10) {
            cout << "LOSE" << endl;
            return 0;
        }
    }
    assert(false);
}