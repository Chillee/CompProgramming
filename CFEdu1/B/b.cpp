#include <bits/stdc++.h>

using namespace std;

string S;
int M;
int L, R, K;

int main() {
    cin >> S;
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> L >> R >> K;
        L--;
        string t = S;
        for (int j = L; j < R; j++) {
            int offsetPos = ((j - L) + K) % (R - L) + L;
            S[offsetPos] = t[j];
        }
    }
    cout << S << endl;
}