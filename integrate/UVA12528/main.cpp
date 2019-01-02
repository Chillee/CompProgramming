#include <bits/stdc++.h>

using namespace std;

double simpson(function<double(double)> f, double a, double b) {
    double c = (a + b) / 2;
    return (f(a) + 4 * f(c) + f(b)) * (b - a) / 6;
}
double rec(function<double(double)> f, double a, double b, double eps, double S) {
    double c = (a + b) / 2;
    double S1 = simpson(f, a, c), S2 = simpson(f, c, b), T = S1 + S2;
    if (abs(T - S) <= 15 * eps || b - a < 1e-10)
        return T + (T - S) / 15;
    return rec(f, a, c, eps / 2, S1) + rec(f, c, b, eps / 2, S2);
}
double integrate(function<double(double)> f, double a, double b, double eps = 1e-8) {
    return rec(f, a, b, eps, simpson(f, a, b));
}
int W, D, A, K;
vector<double> coeffs[4];
double func(double x, array<vector<double>, 2> coeffs) {
    double num = 0;
    for (int i = 0; i < coeffs[0].size(); i++) {
        num += coeffs[0][i] * pow(x, i);
    }
    double denom = 0;
    for (int i = 0; i < coeffs[1].size(); i++) {
        denom += coeffs[1][i] * pow(x, i);
    }
    return num / denom;
}
double f(double x, double d) {
    return max(func(x, {coeffs[0], coeffs[1]}), d) - max(func(x, {coeffs[2], coeffs[3]}), d);
    ;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> W) {
        cin >> D >> A >> K;
        for (int j = 0; j < 4; j++) {
            coeffs[j].clear();
            for (int i = 0; i < K + 1; i++) {
                double t;
                cin >> t;
                coeffs[j].push_back(t);
            }
        }
        double l = -D, r = 0;
        for (int i = 0; i < 30; i++) {
            double mid = (l + r) / 2;
            auto cf = [mid](double x) { return f(x, mid); };
            if (integrate(cf, 0, W, 1e-7) > A) {
                l = mid;
            } else {
                r = mid;
            }
        }
        cout << fixed << setprecision(5) << -l << endl;
    }
}