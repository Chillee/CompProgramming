#include <bits/stdc++.h>

using namespace std;

int N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    int cur = 1;
    for (int i = 0; i < N; i++) {
        string t;
        cin >> t;
        if (t[0] == 'm') {
        } else {
            if (cur != stoi(t)) {
                cout << "something is fishy" << endl;
                return 0;
            }
        }
        cur++;
    }
    cout << "makes sense" << endl;
}