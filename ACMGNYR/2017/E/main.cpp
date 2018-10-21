#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

int P;
int K, M;
long double X;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P;
    for (int t = 0; t < P; t++) {
        cin >> K >> M >> X;
        int bestN = 0, bestD = 1;
        long double bestDiff = 1e9;
        int curDenom = (int)(X * (M / 2 - 1) - 5);
        for (int i = M / 2 - 1; i <= M; i++) {
            double ideal = (X * i);
            while (ideal - curDenom > 0.5) {
                curDenom++;
            }
            if (abs((curDenom / (double)i) - X) < bestDiff) {
                bestN = curDenom;
                bestD = i;
                bestDiff = abs((curDenom / (double)i) - X);
            }
        }
        int dv = __gcd(bestN, bestD);
        cout << K << ' ' << bestN / dv << '/' << bestD / dv << endl;
    }
}