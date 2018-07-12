#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
int N, P;
char S[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> P;
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    for (int i = P; i < N; i++) {
        if (S[i] == '.' || S[i - P] == '.') {
            if (S[i] == '.' && S[i - P] == '.') {
                S[i] = '0';
                S[i - P] = '1';
            } else if (S[i] == '.') {
                S[i] = (S[i - P] == '1' ? '0' : '1');
            } else {
                S[i - P] = (S[i] == '1' ? '0' : '1');
            }
            for (int j = 0; j < N; j++) {
                if (S[j] == '.') {
                    cout << '0';
                } else {
                    cout << S[j];
                }
            }
            cout << endl;
            return 0;
        }
    }
    for (int i = P; i < N; i++) {
        if (S[i] != S[i - P]) {
            for (int j = 0; j < N; j++) {
                if (S[j] == '.') {
                    cout << '0';
                } else {
                    cout << S[j];
                }
            }
            cout << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}