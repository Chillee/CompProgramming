#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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

template <class P> bool onSegment(P s, P e, P p) { return sgn(s.cross(e, p)) == 0 && sgn((s - p).dot(e - p)) <= 0; }
bool crossesRay(P a, P p, P q) { return sgn(((a.y >= q.y) - (a.y >= p.y)) * a.cross(p, q)) > 0; }
bool inPolygon(vector<P> &p, P a, bool strict = true) {
    int nCross = 0, n = sz(p);
    rep(i, 0, n) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        nCross += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return nCross & 1;
}

ostream &operator<<(ostream &os, P p) { return cout << p.x + EPS << " " << p.y + EPS; }
istream &operator>>(istream &is, P p) { return cin >> p.x >> p.y; }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
}