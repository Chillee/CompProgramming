#include <bits/stdc++.h>

using namespace std;

int N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        sum1 += t;
    }
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        sum2 += t;
    }
    cout << (sum1 >= sum2 ? "Yes" : "No") << endl;
}
