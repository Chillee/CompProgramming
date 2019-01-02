#include <bits/stdc++.h>

using namespace std;

string S;
int N;
int main() {
    cin >> N;
    cin >> S;
    int A = 0, D = 0;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == 'A')
            A++;
        else if (S[i] == 'D')
            D++;
    }
    if (A > D) {
        cout << "Anton" << endl;
    } else if (D > A) {
        cout << "Danik" << endl;
    } else {
        cout << "Friendship" << endl;
    }
}