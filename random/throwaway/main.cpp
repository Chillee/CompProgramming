#include <bits/stdc++.h>

using namespace std;

typedef double T;
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
    return [o](pt v, pt w) { return make_tuple(half(v - o), 0, v.sq()) < make_tuple(half(w - o), cross(v - o, w - o), w.sq()); };
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
/* Circle Start */
struct circle {
    pt c;
    double r;
};
pt circumCenter(pt a, pt b, pt c) {
    b = b - a, c = c - a;     // consider coordinates relative to A
    assert(cross(b, c) != 0); // no circumcircle if A,B,C aligned
    return a + (b * c.sq() - c * b.sq()).perp() / cross(b, c) / 2;
}
double circumRadius(pt a, pt b, pt c) { return (a - b).abs() * (b - c).abs() * (c - a).abs() / abs(orient(a, b, c)) / 2.; }
circle circumCircle(pt a, pt b, pt c) { return {circumCenter(a, b, c), circumRadius(a, b, c)}; }
int circleLine(circle c, line l, pair<pt, pt> &out) {
    double h2 = c.r * c.r - l.sqDist(c.c);
    if (h2 >= 0) {                         // the line touches the circle
        pt p = l.proj(c.c);                // point P
        pt h = l.v * sqrt(h2) / l.v.abs(); // vector parallel to l, of length h
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}
int circleCircle(circle c1, circle c2, pair<pt, pt> &out) {
    pt d = c2.c - c1.c;
    double d2 = d.sq();
    if (d2 == 0) { // concentric circles
        assert(c1.r != c2.r);
        return 0;
    }
    double pd = (d2 + c1.r * c1.r - c2.r * c2.r) / 2; // = |O_1P| * d
    double h2 = c1.r * c1.r - pd * pd / d2;           // = hˆ2
    if (h2 >= 0) {
        pt p = c1.c + d * pd / d2, h = d.perp() * sqrt(h2 / d2);
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}
int tangents(circle c1, circle c2, bool inner, vector<pair<pt, pt>> &out) {
    if (inner)
        c2.r = -c2.r;
    pt d = c2.c - c1.c;
    double dr = c1.r - c2.r, d2 = d.sq(), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) {
        assert(h2 != 0);
        return 0;
    }
    for (int sign : {-1, 1}) {
        pt v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
        out.push_back({c1.c + v * c1.r, c2.c + v * c2.r});
    }
    return 1 + (h2 > 0);
}

// IMPORTANT: random_shuffle(pts.begin(), pts.end())
circle MEC(vector<pt> &pts, vector<pt> ch = {}) { // Minimum Enclosing Circle
    if (pts.empty() || ch.size() == 3) {
        if (ch.size() == 0)
            return {0, -1};
        else if (ch.size() == 1)
            return {ch[0], 0};
        else if (ch.size() == 2)
            return {(ch[0] + ch[1]) / 2, (ch[0] - ch[1]).abs() / 2};
        else
            return circumCircle(ch[0], ch[1], ch[2]);
    }
    auto p = pts.back();
    pts.pop_back();
    auto c = MEC(pts, ch);
    if (sgn((p - c.c).abs() - c.r) > 0) {
        ch.push_back(p);
        c = MEC(pts, ch);
    }
    pts.push_back(p);
    return c;
}
/* Circle End */
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<pt> pts = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
    cout << MEC(pts).c << endl;
}