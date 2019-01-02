#include <bits/stdc++.h>
using namespace std;

#define int long long

void out(vector<int> a) {
    for (int i : a)
        cout << i << ' ';
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    if (n == 1 || n * (n - 1) / 2 == m) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        vector<int> a;
        for (int i = 0; i < n; i++) {
            a.push_back(i + 1);
        }
        out(a);

        vector<int> deg(n + 1);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            if (x > y)
                swap(x, y);
            deg[y]++;
        }

        for (int i = 1; i <= n; i++) {
            if (deg[i] != i - 1) {
                a[i - 1]--;
                out(a);
                return 0;
            }
        }
    }

    return 0;
}