#include <bits/stdc++.h>

using namespace std;

int N, K;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    vector<int> vals;
    for (int i = 1; i < K; i++) {
        if (N % i != 0)
            continue;
        int b = N / i;
        for (int j = b * K; j < b * K + K; j++) {
            if (j % K == i && (j / K) * i == N) {
                vals.push_back(j);
            }
        }
    }
    sort(vals.begin(), vals.end());
    cout << vals[0] << endl;
}