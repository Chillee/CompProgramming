#include <bits/stdc++.h>

using namespace std;

int N;
int A[20];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < (1 << N); i++) {
        bitset<20> cur(i);
        int res = 0;
        for (int j = 0; j < N; j++) {
            if (cur[j]) {
                res += A[j];
            } else {
                res -= A[j];
            }
        }
        if (((res % 360) + 360) % 360 == 0) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
}