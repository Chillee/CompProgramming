#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
int P, K, N;
int A[MAXN];
bool moved[MAXN];
int main() {
    cin >> P;
    for (int p = 0; p < P; p++) {
        cin >> K >> N;
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        for (int i = 0; i < N; i++) {
            moved[i] = false;
        }
        for (int i = 0; i < N; i++) {
            bool needsMov = false;
            for (int j = i + 1; j < N; j++) {
                if (A[j] < A[i]) {
                    needsMov = true;
                    break;
                }
            }
            if (needsMov) {
                moved[i] = true;
                for (int j = i; j < N; j++) {
                    if (A[j] > A[i])
                        moved[j] = true;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < N; i++) {
            ans += moved[i];
        }
        cout << K << " " << ans << endl;
    }
}