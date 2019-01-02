#include <bits/stdc++.h>

using namespace std;

int N, D;
int X[105];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> D;
    for (int i = 0; i < N; i++) {
        cin >> X[i];
    }
    sort(X, X + N);
    int ans = 2;
    for (int i = 0; i < N - 1; i++) {
        if (X[i + 1] - X[i] > 2 * D) {
            ans += 2;
        } else if (X[i + 1] - X[i] == 2 * D) {
            ans++;
        }
    }
    cout << ans << endl;
}