#include <bits/stdc++.h>

const int N = 1e6 + 10;

using namespace std;
bool mark[500];

int main() {
    int n;
    cin >> n;
    int mx = 1e9 + 7;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if (x > y)
            swap(x, y);
        if (x > mx) {
            return cout << "NO", 0;
        }
        if (y <= mx)
            mx = y;
        else
            mx = x;
    }
    cout << "YES" << endl;
}