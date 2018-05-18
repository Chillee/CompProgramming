#include <bits/stdc++.h>

using namespace std;

int N;
int numZero, numOnes;
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        if (c == '0')
            numZero++;
        else if (c == '1')
            numOnes++;
    }
    if (numOnes >= 1) {
        cout << "1";
    }
    for (int i = 0; i < numZero; i++) {
        cout << "0";
    }
    cout << endl;
}