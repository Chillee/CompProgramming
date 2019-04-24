#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> vals = {1, 2, 3, 4, 5};
    do {
        bool found = true;
        for (int i = 0; i < vals.size() - 2; i += 2) {
            if (vals[i] > vals[i + 1] && vals[i + 1] < vals[i + 2])
                continue;
            else {
                found = false;
            }
        }
        if (found) {
            for (auto i : vals)
                cout << i << ' ';
            cout << endl;
        }
    } while (next_permutation(all(vals)));
}