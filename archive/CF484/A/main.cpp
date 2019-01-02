#include <bits/stdc++.h>

using namespace std;

int N;
string S;
int main() {
    cin >> N;
    cin >> S;
    S = "0" + S + "0";
    for (int i = 1; i <= N; i++) {
        if (S[i] == '0' && (S[i - 1] == '0' && S[i + 1] == '0')) {
            cout << "No" << endl;
            return 0;
        }
        if (S[i] == '1' && (S[i - 1] == '1' || S[i + 1] == '1')) {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}