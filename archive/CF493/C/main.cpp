#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N, X, Y;
string A;
ll numRanges;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> X >> Y;
    cin >> A;
    bool inRange = false;
    for (ll i = 0; i < N; i++) {
        if (!inRange && A[i] == '0') {
            inRange = true;
            numRanges++;
        } else if (inRange && A[i] == '1') {
            inRange = false;
        }
    }
    ll ans1 = numRanges * Y;
    ll ans2 = max(numRanges - 1, 0LL) * X + Y;
    cout << min(ans1, ans2) << endl;
}