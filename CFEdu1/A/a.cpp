#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll T, N;

ll result;
int main() {
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N;
        result = N * (N + 1) / 2;
        for (ll t = 1; t <= N; t *= 2) {
            result -= 2 * t;
        }
        cout << result << endl;
    }
}