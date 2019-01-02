#include <bits/stdc++.h>

using namespace std;

int P;
int K, N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P;
    for (int p = 0; p < P; p++) {
        cin >> K >> N;
        int num = 1, denom = 1;
        bitset<32> val(N);
        bool start = false;
        for (int i = 31; i >= 0; i--) {
            if (start) {
                if (val[i]) {
                    num = num + denom;
                } else {
                    denom = denom + num;
                }
            }
            if (val[i]) {
                start = true;
            }
        }
        cout << K << " " << num << "/" << denom << endl;
    }
}