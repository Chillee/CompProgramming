#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
int A;
ld B;
int main() {
    cin >> A >> B;
    long double best = 10000;
    int a, b, c;
    for (int i = 1; i <= A - 2; i++) {
        long double cur = abs(B - (360.0 / A) * i / 2.0);
        if (best > cur) {
            best = cur;
            a = 0;
            b = i + 1;
            c = i;
        }
    }
    cout << a + 1 << ' ' << b + 1 << ' ' << c + 1 << endl;
}