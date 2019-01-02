#include <bits/stdc++.h>

using namespace std;

int N, A, B;
string S;
int main() {
    cin >> N >> A >> B;
    cin >> S;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == '*')
            continue;
        if (i == 0 || S[i - 1] == '*') {
            if (A > B && A > 0) {
                S[i] = 'a';
                A--;
            } else if (A <= B && B > 0) {
                S[i] = 'b';
                B--;
            }
        } else {
            if (i > 0 && S[i - 1] != 'b' && B > 0) {
                S[i] = 'b';
                B--;
            } else if (i > 0 && S[i - 1] != 'a' && A > 0) {
                S[i] = 'a';
                A--;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == 'a' || S[i] == 'b') {
            ans++;
        }
    }
    cout << ans << endl;
}