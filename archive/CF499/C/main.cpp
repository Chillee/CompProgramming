#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const double EPS = 1e-6;
int N, M;
int A[MAXN], B[MAXN];
bool f(double x) {
    double cur = x;
    for (int i = 0; i < N; i++) {
        cur -= (cur + M) / A[i];
        if (cur < 0)
            return false;
        cur -= (cur + M) / B[i];
        if (cur < 0)
            return false;
    }
    return true;
}
double binSearch(double l, double r) {
    double mid = (l + r) / 2;
    if (abs(r - l) < EPS)
        return l;
    if (f(mid)) {
        return binSearch(l, mid);
    } else {
        return binSearch(mid, r);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }
    double ans = binSearch(0, 1e9 + 10);
    if (ans > 1e9) {
        cout << -1 << endl;
        return 0;
    }
    cout << setprecision(12) << ans << endl;
}