#include <bits/stdc++.h>

using namespace std;

int P;
int K, N;
int main() {
    cin >> P;
    for (int p = 0; p < P; p++) {
        cin >> K >> N;
        int num = 1, denom = 1;
        int H = sizeof(int) * 8 - __builtin_clz(N);
        for (int i = H - 2; i >= 0; i--) {
            if (1 << i & N) {
                num = num + denom;
            } else {
                denom = num + denom;
            }
        }
        cout << K << " " << num << "/" << denom << endl;
    }
}