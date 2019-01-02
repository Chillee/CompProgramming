
#include <bits/stdc++.h>
using namespace std;

int n, a, b;
string s;
vector<int> v;

int main() {

    cin >> n >> a >> b >> s;
    int ans = 0;
    int points = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '.')
            points++;
        else if (points != 0) {
            v.push_back(points);
            points = 0;
        }
    }
    if (points != 0) {
        v.push_back(points);
    }
    sort(v.begin(), v.end());
    for (int i = v.size() - 1; i >= 0; i--) {
        if (a == 0 && b == 0)
            break;
        if (v[i] % 2 == 0) {
            int mn = min(v[i] / 2, b);
            b -= mn;
            ans += mn;
            mn = min(v[i] / 2, a);
            a -= mn;
            ans += mn;
        } else {
            int mn = min(v[i] / 2, b);
            b -= mn;
            ans += mn;
            mn = min(v[i] / 2, a);
            a -= mn;
            ans += mn;
            if (a > b && a >= 1) {
                ans += 1;
                a--;
            } else if (b > a && b >= 1) {
                ans += 1;
                b--;
            } else if (a >= 1 && b >= 1) {
                ans += 1;
                a--;
            }
        }
    }
    cout << ans;
}
