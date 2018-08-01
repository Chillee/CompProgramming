#include <bits/stdc++.h>
#define vi vector<int>
#define pp pair<int, int>
#define all(x) x.begin(), x.end()
#define pb push_back
#define int long long
#define forx(i, x) for (int i = 0; i < x; i++)
using namespace std;
main() {
    int m, n;
    cin >> m >> n;
    int lo = 1;
    int high = m;
    //	int lo1=0;
    //	int high1=
    int mid = (lo + high) / 2;
    vi color(n, -1);
    int ans;
    for (int i = 0; i < n; i++) {
        // ans;
        cout << lo << endl;
        cin >> ans;
        if (ans == 0 or ans == -2) {
            exit(0);
        }
        if (ans == -1) {
            color[i] = 0;
        } else {
            color[i] = 1;
        }
    }
    int j = 0;
    while (lo <= high) {
        int mid = (lo + high) / 2;
        cout << mid << endl;
        cin >> ans;
        if (ans == 0 or ans == -2) {
            exit(0);
        }
        if (color[j] == 0) {
            ans = -ans;
        }
        if (ans == 1) {
            lo = mid + 1;

        } else {
            high = mid - 1;
        }
        j++;
    }
}