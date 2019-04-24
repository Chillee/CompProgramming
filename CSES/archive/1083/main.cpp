#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> vals;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int x;
        cin >> x;
        vals.push_back(x);
    }
    sort(vals.begin(), vals.end());
    vals.push_back(0);
    for (int i = 0; i < N; i++) {
        if (vals[i] != i + 1) {
            cout << i + 1 << endl;
            return 0;
        }
    }
}