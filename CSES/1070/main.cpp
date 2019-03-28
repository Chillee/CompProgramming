#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin >> N;
    if (N == 1)
        cout << 1 << endl;
    else if (N <= 3)
        cout << "NO SOLUTION" << endl;
    else if (N == 4)
        cout << "2 4 1 3" << endl;
    else {
        for (int i = 1; i <= N; i += 2)
            cout << i << ' ';
        for (int i = 2; i <= N; i += 2)
            cout << i << ' ';
    }
}