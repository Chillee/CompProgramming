
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const ld PI = acos(-1);
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define f first
#define s second

ll sqr(ll a) { return a * a; }

int main() {

    ios::sync_with_stdio(false);

    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(all(a));
    a.push_back(2e9);

    if (k == 0) {
        if (a[0] == 2)
            cout << 1;
        else
            cout << -1;
        return 0;
    }

    k--;
    if (a[k] == a[k + 1])
        cout << -1;
    else
        cout << a[k];
}
