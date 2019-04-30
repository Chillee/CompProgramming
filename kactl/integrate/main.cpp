#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

typedef double d;
#define S(a, b) (f(a) + 4 * f((a + b) / 2) + f(b)) * (b - a) / 6

template <class F> d rec(F f, d a, d b, d eps, d S) {
    d c = (a + b) / 2;
    d S1 = S(a, c);
    d S2 = S(c, b), T = S1 + S2;
    if (abs(T - S) <= 15 * eps || b - a < 1e-10)
        return T + (T - S) / 15;
    return rec(f, a, c, eps / 2, S1) + rec(f, c, b, eps / 2, S2);
}
template <class F> d quad(d a, d b, F f, d eps = 1e-8) { return rec(f, a, b, eps, S(a, b)); }

// double z, y;
// auto h = [y, z](double x) { return x * x + y * y + z * z <= 1; };
// auto g = [&y](double y) {
//     ::y = y;
//     return quad(h, -1, 1)
// };
// auto f = []
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    double sphereVol = quad(-1, 1, [](double x) {
        return quad(-1, 1,
                    [x](double y) { return quad(-1, 1, [x, y](double z) { return x * x + y * y + z * z <= 1; }); });
    });
    double pi = sphereVol * 3 / 4;
    cout << pi << endl;
}