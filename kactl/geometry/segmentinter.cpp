
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

template <class P> bool onSegment(P s, P e, P p) { return sgn(s.cross(e, p)) == 0 && sgn((s - p).dot(e - p)) <= 0; }
template <class P> bool segInterProper(P a, P b, P c, P d, P &out) {
    double oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c), od = a.cross(b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}
template <class P> set<P> segInter(P a, P b, P c, P d) {
    P out;
    if (segInterProper(a, b, c, d, out))
        return {out};
    set<P> s;
    if (onSegment(c, d, a))
        s.insert(a);
    if (onSegment(c, d, b))
        s.insert(b);
    if (onSegment(a, b, c))
        s.insert(c);
    if (onSegment(a, b, d))
        s.insert(d);
    return s;
}
typedef Point<double> P;
ostream &operator<<(ostream &os, P p) { return cout << p.x + EPS << " " << p.y + EPS; }
istream &operator>>(istream &is, P p) { return cin >> p.x >> p.y; }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin >> N;
    cout << fixed << setprecision(2);
    for (int i = 0; i < N; i++) {
        P a, b, c, d;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
        auto res = segInter(a, b, c, d);
        if (res.size() == 0) {
            cout << "none" << endl;
        } else if (res.size() == 1) {
            cout << *res.begin() << endl;
        } else {
            vector<P> t(res.begin(), res.end());
            cout << t[0] << ' ' << t[1] << endl;
        }
    }
}