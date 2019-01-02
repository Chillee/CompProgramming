#include <bits/stdc++.h>

using namespace std;

// typedef long double double;
#define double long double

double simpson(function<double(double)> f, double a, double b) {
    double c = (a + b) / 2;
    // return (b - a) / 6 * (f(a) + 4 * f(c) + f(b));
    return (f(a) + 4 * f(c) + f(b)) * (b - a) / 6;
}
double rec(function<double(double)> f, double a, double b, double eps, double S, bool rel = true) {
    double c = (a + b) / 2;
    double S1 = simpson(f, a, c), S2 = simpson(f, c, b), T = S1 + S2;
    if (abs(T - S) <= 15 * eps || b - a < 1e-10 || (rel && abs((T - S) / S) <= 15 * eps))
        return T + (T - S) / 15;
    return rec(f, a, c, eps / 2, S1, rel) + rec(f, c, b, eps / 2, S2, rel);
}
double integrate(function<double(double)> f, double a, double b, double eps = 1e-8, bool rel = true) {
    return rec(f, a, b, eps, simpson(f, a, b), rel);
}

int cnt = 0;
unordered_map<double, double> memo;
double f(double x) {
    if (memo.count(x))
        return memo[x];
    cnt++;
    memo[x] = 1 / sqrt(x);
    return memo[x];
    // return pow(x, x);
    // return sin(x);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    double eps = 1e-3;
    clock_t begin;
    begin = clock();
    cout << fixed << setprecision(20) << integrate(f, 1e-15, 1, eps, false) << endl;
    cout << cnt << endl;
    cout << (clock() - begin) / (CLOCKS_PER_SEC + 0.) << endl;
    cout << endl;
    cnt = 0, memo.clear();
    begin = clock();
    cout << fixed << setprecision(20) << integrate(f, 1e-15, 1, eps, true) << endl;
    cout << cnt << endl;
    cout << (clock() - begin) / (CLOCKS_PER_SEC + 0.) << endl;
    cout << endl;
    // cnt = 0;
    // begin = clock();
    // cout << fixed << setprecision(20) << integrate(f, 0, 10, eps) << endl;
    // cout << cnt << endl;
    // cout << (clock() - begin) / (CLOCKS_PER_SEC + 0.) << endl;
}
// 3057488.91415005223825573921