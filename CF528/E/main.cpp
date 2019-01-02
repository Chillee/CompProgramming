#include <bits/stdc++.h>

using namespace std;

int T, K;
string S, A, B;
int tmp[26], rtmp[26];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> K;
        cin >> S >> A >> B;
        fill(tmp, tmp + 26, -1);
        fill(rtmp, rtmp + 26, -1);
        bool res = true;
        [&]() {
            for (int i = 0; i < S.size(); i++) {
                if (tmp[S[i]] != -1 && (tmp[S[i]] < A[i] - 26 || tmp[S[i]] > B[i] - 26)) {
                    res = false;
                }
                if (A[i] + 1 < B[i]) {
                    for (int j = A[i] + 1; j < B[i]; j++) {
                        if (tmp[j - 'a'] != -1) {
                            tmp[j - 'a'] = ;
                            return;
                        }
                    }
                }
            }
            return true;
        }
    }
}