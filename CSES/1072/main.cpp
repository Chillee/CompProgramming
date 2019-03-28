#include <bits/stdc++.h>

using namespace std;

int N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (long long i = 1; i <= N; i++)
        cout << (i - 1) * (i + 4) * (i * i - 3 * i + 4) / 2 << endl;
}