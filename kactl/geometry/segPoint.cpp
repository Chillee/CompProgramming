#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

const double EPS = 1e-8;
template <typename T> int sgn(T x) { return x < -EPS ? -1 : x > EPS; }
template <class T> struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const { return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
};
typedef Point<double> P;

template <class P> double lineDist(const P &a, const P &b, const P &p) {
    return (double)(b - a).cross(p - a) / (b - a).dist();
}
double segDist(P a, P b, P p) {
    if (!(a == b)) {
        auto ap = (a - b).dot(a), pp = (a - b).dot(p), bp = (a - b).dot(p);
        if (ap < pp && pp < bp)
            return lineDist(a, b, p);
    }
    return min((p - a).dist(), (p - b).dist());
}

ostream &operator<<(ostream &os, P p) { return cout << p.x + EPS << " " << p.y + EPS; }
istream &operator>>(istream &is, P p) { return cin >> p.x >> p.y; }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
}