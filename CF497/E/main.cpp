#include <bits/stdc++.h>

using namespace std;

int N;
// int binSearch(int l, int r) {
//     int mid = (l + r) / 2;
//     cout << mid << ' ' << N << endl;
//     int res;
//     cin >> res;
//     if (res == )
// }
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    int la = 1, ra = N, lb = 1, rb = N;
    int res;
    while (true) {
        cout << la << ' ' << lb << endl;
        cin >> res;
        if (res == 1) {
            cout << (la + ra) / 2 << ' ' << lb << endl;
            cin >> res;
            if (res == 3) {
                ra = (la + ra) / 2;
            } else if (res == 2) {
            }
        }
    }
}