#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;
/** Constants Start **/
const double PI = acos(-1.0);
const double EPS = 1e-8;
const double INF = 1e9 + 5;
template <typename T> int sgn(T x) { return x < -EPS ? -1 : x > EPS; }
/** Constants End **/
/** Base Start **/
struct pt {
    T x, y;
    pt operator+(pt p) { return {x + p.x, y + p.y}; }
    pt operator-(pt p) { return {x - p.x, y - p.y}; }
    pt operator-() { return {-x, -y}; }
    pt operator*(pt p) { return {x * p.x, y * p.y}; }
    pt operator*(T d) { return {x * d, y * d}; }
    pt operator/(T d) { return {x / d, y / d}; }
    bool operator==(pt p) { return x == p.x && y == p.y; }
    bool operator!=(pt p) { return !(*this == p); }
    bool operator<(pt p) const { return make_pair(x, y) < make_pair(p.x, p.y); }
    bool operator>(pt p) { return p < *this; }
    T sq() { return x * x + y * y; }
    double abs() { return sqrt(sq()); }
    pt translate(pt v) { return *this + v; }
    pt perp() { return {-y, x}; }
    pt rot(double a) { return {x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)}; }
};
ostream &operator<<(ostream &os, pt p) { return cout << "(" << p.x << "," << p.y << ")"; }
istream &operator>>(istream &is, pt p) { return cin >> p.x >> p.y; }
pt scale(pt c, double factor, pt p) { return c + (p - c) * factor; }
T dot(pt v, pt w) { return v.x * w.x + v.y * w.y; }
T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }
int orientS(pt a, pt b, pt c) { return sgn(orient(a, b, c)); }
T orient(pt b, pt c) { return cross(b, c); }
bool half(pt p) {
    assert(p.x != 0 || p.y != 0);
    return p.y > 0 || (p.y == 0 && p.x < 0);
}
auto polarCmp(pt o = {0, 0}) {
    return [o](pt v, pt w) {
        return make_tuple(half(v - o), 0, v.sq()) < make_tuple(half(w - o), cross(v - o, w - o), w.sq());
    };
}
struct line {
    pt v;
    T c;
    line() {}
    // From direction vector v and y-intercept c
    line(pt v, T c) : v(v), c(c) { assert(v.sq() != 0); }
    // From equation ax+by=c
    line(T a, T b, T c) : v({b, -a}), c(c) { assert(v.sq() != 0); }
    // From points P and Q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) { assert(v.sq() != 0); }
    // - these work with T = int
    T side(pt p) { return cross(v, p) - c; }
    double dist(pt p) { return abs(side(p)) / v.abs(); }
    double sqDist(pt p) { return side(p) * side(p) / (double)v.sq(); }
    line perpThrough(pt p) { return {p, p + v.perp()}; }
    bool cmpProj(pt p, pt q) { return dot(v, p) < dot(v, q); }
    line translate(pt t) { return {v, c + cross(v, t)}; }
    // - these require T = double
    line shiftLeft(double dist) { return {v, c + dist * v.abs()}; }
    pt proj(pt p) { return p - v.perp() * side(p) / v.sq(); }
    pt refl(pt p) { return p - v.perp() * 2 * side(p) / v.sq(); }
};
pair<bool, pt> inter(line l1, line l2) {
    T d = cross(l1.v, l2.v);
    if (d == 0)
        return {false, pt{0, 0}};
    return {true, (l2.v * l1.c - l1.v * l2.c) / d}; // requires floating-point coordinates
}
bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    double oa = orient(c, d, a), ob = orient(c, d, b), oc = orient(a, b, c), od = orient(a, b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}
bool inDisk(pt a, pt b, pt p) { return dot(a - p, b - p) <= 0; }
bool onSegment(pt a, pt b, pt p) { return orientS(a, b, p) == 0 && inDisk(a, b, p); }
/** Base End **/
/** Line Segment Start **/
set<pt> inters(pt a, pt b, pt c, pt d) {
    pt out;
    if (properInter(a, b, c, d, out))
        return {out};
    set<pt> s;
    if (onSegment(c, d, a) == true)
        s.insert(a);
    if (onSegment(c, d, b))
        s.insert(b);
    if (onSegment(a, b, c))
        s.insert(c);
    if (onSegment(a, b, d))
        s.insert(d);
    return s;
}
double segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) // if closest to projection
            return l.dist(p);                   // output distance to line
    }
    return min((p - a).abs(), (p - b).abs()); // otherwise distance to A or B
}
double segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a, b, c, d, dummy))
        return 0;
    return min({segPoint(a, b, c), segPoint(a, b, d), segPoint(c, d, a), segPoint(c, d, b)});
}
/** Line Segment End **/
/* Polygon Start */
double areaTriangle(pt a, pt b, pt c) { return abs(cross(b - a, c - a)) / 2.0; }
T areaPolygon(vector<pt> p) { // if negative, p is in clock-wise order.
    T area = cross(p.back(), p[]) for (int i = 0, n = p.size(); i < n; i++) area +=
        cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n -1
    return area;                     // Returns double the area.
}
// true if P at least as high as A (blue part)
bool above(pt a, pt p) { return p.y >= a.y; }
// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) { return (above(q, a) - above(p, a)) * orient(a, p, q) > 0; }
// if strict, returns false when A is on the boundary
bool inPolygon(vector<pt> &p, pt a, bool strict = true) { // O(n)
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}
/* Polygon End */

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}