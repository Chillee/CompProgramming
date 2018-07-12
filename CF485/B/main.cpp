#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll X, Y;

ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base, exp / 2) * (exp % 2 == 1 ? base : 1);
}

int main() {
    cin >> X >> Y;
    if ((X < 10 && Y < 10) || (X == 1) || (Y == 1)) {
        if (bin_exp(X, Y) > bin_exp(Y, X)) {
            cout << ">" << endl;
        } else if (bin_exp(X, Y) == bin_exp(Y, X)) {
            cout << "=" << endl;
        } else {
            cout << "<" << endl;
        }
    } else {
        if (X > Y) {
            cout << "<" << endl;
        } else if (X < Y) {
            cout << ">" << endl;
        } else {
            cout << "=" << endl;
        }
    }
}