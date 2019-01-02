#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

int roads[4][4];
int norm(int x) { return ((x % 4) + 4) % 4; }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> roads[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        if (roads[norm(i)][0] && roads[norm(i - 1)][3] || roads[norm(i)][1] && roads[norm(i + 2)][3] ||
            roads[norm(i)][2] && roads[norm(i + 1)][3]) {
            cout << "YES" << endl;
            return 0;
        }
        if (roads[norm(i)][3]) {
            for (int j = 0; j < 3; j++) {
                if (roads[norm(i)][j]) {
                    cout << "YES" << endl;
                    return 0;
                }
            }
        }
    }
    cout << "NO" << endl;
}