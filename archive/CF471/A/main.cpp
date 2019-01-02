#include <bits/stdc++.h>

using namespace std;

double HH, MM;
double H, D, C, N;
int main() {
    cin >> HH >> MM;
    cin >> H >> D >> C >> N;
    double ans = 1e10;
    if (HH >= 20) {
        ans = ((int)(H + N - 1) / (int)N) * C * .8;
        cout << ans << endl;
        return 0;
    } else {
        ans = ((int)(H + N - 1) / (int)N) * C;
    }
    double minDiff = (20 - HH) * 60 - MM;
    double ans2 = ((int)(H + minDiff * D + N - 1) / (int)N) * C * 0.8;
    printf("%.3lf", min(ans, ans2));
    return 0;
}