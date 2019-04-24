#include <bits/stdc++.h>
using namespace std;
signed main() {
    long long N;
    scanf("%d", &N);
    while (N != 1) {
        cout << N << ' ';
        if (N & 1)
            N = N * 3 + 1;
        else
            N /= 2;
    }
    cout << 1 << endl;
}