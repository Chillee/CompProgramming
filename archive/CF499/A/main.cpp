#include <bits/stdc++.h>

using namespace std;

int N, K;
string S;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    cin >> S;
    sort(S.begin(), S.end());
    int ans = 0;
    int idx = 0;
    int prevChar = -100;
    for (int i = 0; i < K; i++) {
        while (idx < S.size() && S[idx] - 'a' - prevChar <= 1) {
            idx++;
        }
        if (idx == S.size()) {
            cout << -1 << endl;
            return 0;
        }
        ans += S[idx] - 'a';
        prevChar = S[idx] - 'a';
    }
    cout << ans + K << endl;
}