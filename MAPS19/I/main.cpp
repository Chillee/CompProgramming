#include <bits/stdc++.h>

using namespace std;

const double LIM = 1e6;

int N;
typedef double T;
/** Constants Start **/
const double PI = acos(-1.0);
const double EPS = 1e-8;
const double INF = 1e9 + 5;
/** Constants End **/
/** Point Start **/
struct pt {
    T x, y;
    pt operator+(pt p) { return {x + p.x, y + p.y}; }
    pt operator-(pt p) { return {x - p.x, y - p.y}; }
    pt operator-() { return {-x, -y}; }
    pt operator*(pt p) { return {x * p.x, y * p.y}; }
    pt operator*(T d) { return {x * d, y * d}; }
    pt operator/(T d) { return {x / d, y / d}; }
};
bool operator==(pt a, pt b) { return a.x == b.x && a.y == b.y; }
bool operator!=(pt a, pt b) { return !(a == b); }
bool operator<(pt a, pt b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); }
bool operator>(pt a, pt b) { return b < a; }
ostream &operator<<(ostream &os, pt p) { return cout << "(" << p.x << "," << p.y << ")"; }
istream &operator>>(istream &is, pt &p) { return cin >> p.x >> p.y; }
T sq(pt p) { return p.x * p.x + p.y * p.y; }
double abs(pt p) { return sqrt(sq(p)); }
template <typename T> int sgn(T x) { return x < -EPS ? -1 : x > EPS; }
pt translate(pt v, pt p) { return p + v; }
pt scale(pt c, double factor, pt p) { return c + (p - c) * factor; }
pt rot(pt p, double a) { return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)}; }
pt perp(pt p) { return {-p.y, p.x}; }
T dot(pt v, pt w) { return v.x * w.x + v.y * w.y; }
T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }
pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) {
    pt pq = q - p, num{cross(pq, fq - fp), dot(pq, fq - fp)};
    return fp + pt{cross(r - p, num), dot(r - p, num)} / sq(pq);
}
bool isPerp(pt v, pt w) { return dot(v, w) == 0; }
double angle(pt a, pt b, pt c) {
    double cosTheta = dot(b - a, c - a) / abs(b - a) / abs(c - a);
    if (cosTheta > 1.0)
        cosTheta = 1.0;
    else if (cosTheta < -1.0)
        cosTheta = -1.0;
    return acos(cosTheta);
}
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }
int orientS(pt a, pt b, pt c) { return sgn(orient(a, b, c)); }
T orient(pt b, pt c) { return cross(b, c); }
bool inAngle(pt a, pt b, pt c, pt x) {
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0)
        swap(b, c);
    return orient(a, b, x) >= 0 && orient(a, c, x) <= 0;
}
double orientedAngle(pt a, pt b, pt c) {
    if (orient(a, b, c) >= 0)
        return angle(a, b, c);
    else
        return 2 * PI - angle(a, b, c);
}
bool isConvex(vector<pt> &p) {
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = p.size(); i < n; i++) {
        int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0)
            hasPos = true;
        if (o < 0)
            hasNeg = true;
    }
    return !(hasPos && hasNeg);
}
bool half(pt p) {
    assert(p.x != 0 || p.y != 0);
    return p.y > 0 || (p.y == 0 && p.x < 0);
}
auto polarCmp(pt o = {0, 0}) {
    return [o](pt v, pt w) { return make_tuple(half(v - o), 0, sq(v)) < make_tuple(half(w - o), cross(v - o, w - o), sq(w)); };
}
/* Point End */
/* Line Start */
struct line {
    pt v;
    T c;
    line() {}
    // From direction vector v and y-intercept c
    line(pt v, T c) : v(v), c(c) { assert(sq(v) != 0); }
    // From equation ax+by=c
    line(T a, T b, T c) : v({b, -a}), c(c) { assert(sq(v) != 0); }
    // From points P and Q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) { assert(sq(v) != 0); }
    // - these work with T = int
    T side(pt p) { return cross(v, p) - c; }
    double dist(pt p) { return abs(side(p)) / abs(v); }
    double sqDist(pt p) { return side(p) * side(p) / (double)sq(v); }
    line perpThrough(pt p) { return {p, p + perp(v)}; }
    bool cmpProj(pt p, pt q) { return dot(v, p) < dot(v, q); }
    line translate(pt t) { return {v, c + cross(v, t)}; }
    // - these require T = double
    line shiftLeft(double dist) { return {v, c + dist * abs(v)}; }
    pt proj(pt p) { return p - perp(v) * side(p) / sq(v); }
    pt refl(pt p) { return p - perp(v) * 2 * side(p) / sq(v); }
};
pair<bool, pt> inter(line l1, line l2) {
    T d = cross(l1.v, l2.v);
    if (d == 0)
        return {false, pt{0, 0}};
    return {true, (l2.v * l1.c - l1.v * l2.c) / d}; // requires floating-point coordinates
}
line bisector(line l1, line l2, bool interior) {
    assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
    double sign = interior ? 1 : -1;
    return {l2.v / abs(l2.v) + (l1.v / abs(l1.v)) * sign, l2.c / abs(l2.v) + sign * l1.c / abs(l1.v)};
}
/* Line End */
/* Line Segment Start */
bool inDisk(pt a, pt b, pt p) { return dot(a - p, b - p) <= 0; }
bool onSegment(pt a, pt b, pt p) { return orient(a, b, p) == 0 && inDisk(a, b, p); }
bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    double oa = orient(c, d, a), ob = orient(c, d, b), oc = orient(a, b, c), od = orient(a, b, d);
    // Proper intersection exists iff opposite signs
    if (oa * ob < 0 && oc * od < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}
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
    return min(abs(p - a), abs(p - b)); // otherwise distance to A or B
}
double segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a, b, c, d, dummy))
        return 0;
    return min({segPoint(a, b, c), segPoint(a, b, d), segPoint(c, d, a), segPoint(c, d, b)});
}
/* Line Segment End */
/* Polygon Start */
double areaTriangle(pt a, pt b, pt c) { return abs(cross(b - a, c - a)) / 2.0; }
double areaPolygon(vector<pt> p) { // if negative, p is in clock-wise order.
    double area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n -1
    }
    return area / 2.0;
}
// true if P at least as high as A (blue part)
bool above(pt a, pt p) { return p.y >= a.y; }
// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) { return (above(q, a) - above(p, a)) * orient(a, p, q) > 0; }
// if strict, returns false when A is on the boundary
bool inPolygon(vector<pt> &p, pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}
/* Polygon End */
/* Circle Start */
double circumRadius(pt a, pt b, pt c) { return abs(a - b) * abs(b - c) * abs(c - a) / abs(orient(a, b, c)) / 2.; }
pt circumCenter(pt a, pt b, pt c) {
    b = b - a, c = c - a;
    assert(cross(b, c) != 0); // no circumcircle if A,B,C aligned
    return a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2;
}
int circleLine(pt o, double r, line l, pair<pt, pt> &out) {
    double h2 = r * r - l.sqDist(o);
    if (h2 >= 0) { // the line touches the circle
        pt p = l.proj(o);
        pt h = l.v * sqrt(h2) / abs(l.v);
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}
int circleCircle(pt o1, double r1, pt o2, double r2, pair<pt, pt> &out) {
    pt d = o2 - o1;
    double d2 = sq(d);
    if (d2 == 0) { // concentric circles
        assert(r1 != r2);
        return 0;
    }
    double pd = (d2 + r1 * r1 - r2 * r2) / 2; // = |O_1P| * d
    double h2 = r1 * r1 - pd * pd / d2;       // = hˆ2
    if (h2 >= 0) {
        pt p = o1 + d * pd / d2, h = perp(d) * sqrt(h2 / d2);
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}
int tangents(pt o1, double r1, pt o2, double r2, bool inner, vector<pair<pt, pt>> &out) {
    if (inner)
        r2 = -r2;
    pt d = o2 - o1;
    double dr = r1 - r2, d2 = sq(d), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) {
        assert(h2 != 0);
        return 0;
    }
    for (int sign : {-1, 1}) {
        pt v = (d * dr + perp(d) * sqrt(h2) * sign) / d2;
        out.push_back({o1 + v * r1, o2 + v * r2});
    }
    return 1 + (h2 > 0);
}
/* Circle End */
/* Convex Start */
vector<pt> convexHull(vector<pt> &pts) {
    sort(pts.begin(), pts.end());
    vector<pt> hull;
    for (int phase = 0; phase < 2; ++phase) {
        auto start = hull.size();
        for (auto &point : pts) {
            while (hull.size() >= start + 2 && orient(hull[hull.size() - 2], hull.back(), point) <= 0)
                hull.pop_back();
            hull.push_back(point);
        }
        hull.pop_back();
        reverse(pts.begin(), pts.end());
    }
    if (hull.size() == 2 && hull[0] == hull[1])
        hull.pop_back();
    return hull;
}
// if strict, returns false when A is on the boundary.
bool inConvex(vector<pt> &l, pt p, bool strict = true) {
    int a = 1, b = l.size() - 1, c;
    if (orientS(l[0], l[a], l[b]) > 0)
        swap(a, b);
    if (orientS(l[0], l[a], p) > 0 || orientS(l[0], l[b], p) < 0 || (strict && (orientS(l[0], l[a], p) == 0 || orientS(l[0], l[b], p) == 0)))
        return false;
    while (abs(a - b) > 1) {
        c = (a + b) / 2;
        if (orientS(l[0], l[c], p) > 0)
            b = c;
        else
            a = c;
    }
    return orientS(l[a], l[b], p) < 0 ? true : !strict;
}
// Max distance across a convex polygon
T convexDiameter(vector<pt> &poly) {
    int n = poly.size();
    auto res = T(0);
    for (int i = 0, j = n < 2 ? 0 : 1; i < j; ++i)
        for (;; j = (j + 1) % n) {
            res = max(res, sq(poly[i] - poly[j]));
            if (orient(poly[(j + 1) % n] - poly[j], poly[i + 1] - poly[i]) >= 0)
                break;
        }
    return res;
}
vector<pt> convexConvex(vector<pt> &P, vector<pt> &Q) {
    const int n = P.size(), m = Q.size();
    int a = 0, b = 0, aa = 0, ba = 0;
    enum { Pin, Qin, Unknown } in = Unknown;
    vector<pt> R;
    do {
        int a1 = (a + n - 1) % n, b1 = (b + m - 1) % m;
        double C = cross(P[a] - P[a1], Q[b] - Q[b1]);
        double A = cross(P[a1] - Q[b], P[a] - Q[b]);
        double B = cross(Q[b1] - P[a], Q[b] - P[a]);
        pt r;
        if (properInter(P[a1], P[a], Q[b1], Q[b], r)) {
            if (in == Unknown)
                aa = ba = 0;
            R.push_back(r);
            in = B > 0 ? Pin : (A > 0 ? Qin : in);
        }
        if (C == 0 && B == 0 && A == 0) {
            if (in == Pin) {
                b = (b + 1) % m;
                ++ba;
            } else {
                a = (a + 1) % m;
                ++aa;
            }
        } else if ((C >= 0 && A > 0) || (C < 0 && B <= 0)) {
            if (in == Pin)
                R.push_back(P[a]);
            a = (a + 1) % n;
            ++aa;
        } else {
            if (in == Qin)
                R.push_back(Q[b]);
            b = (b + 1) % m;
            ++ba;
        }
    } while ((aa < n || ba < m) && aa < 2 * n && ba < 2 * m);
    if (in == Unknown) {
        if (inConvex(Q, P[0]))
            return P;
        if (inConvex(P, Q[0]))
            return Q;
    }
    return R;
}

bool checkhp(line &a, line &b, line &me) { return sgn(me.side(inter(a, b).second)) > 0; }
vector<pt> halfPlaneIntersection(vector<line> border) {
    border.push_back(line{pt{-LARGE, -LARGE}, pt{LARGE, -LARGE}});
    border.push_back(line{pt{LARGE, -LARGE}, pt{LARGE, LARGE}});
    border.push_back(line{pt{LARGE, LARGE}, pt{-LARGE, LARGE}});
    border.push_back(line{pt{-LARGE, LARGE}, pt{-LARGE, -LARGE}});

    sort(border.begin(), border.end(), [](auto a, auto b) { return polarCmp()(a.v, b.v); });
    auto eq = [](line a, line b) { return sgn(atan2(a.v.y, a.v.x) - atan2(b.v.y, b.v.x)) == 0; };
    border.resize(unique(border.begin(), border.end(), eq) - border.begin());
    deque<line> deq;
    for (int i = 0; i < border.size(); ++i) {
        line cur = border[i];
        while (deq.size() > 1 && !checkhp(deq[deq.size() - 2], deq[deq.size() - 1], cur))
            deq.pop_back();
        while (deq.size() > 1 && !checkhp(deq[0], deq[1], cur))
            deq.pop_front();
        deq.push_back(cur);
    }
    while (deq.size() > 1 && !checkhp(deq[deq.size() - 2], deq[deq.size() - 1], deq[0]))
        deq.pop_back();
    vector<pt> pts;
    for (int i = 0; i < deq.size(); i++)
        pts.push_back(inter(deq[i], deq[(i + 1) % deq.size()]).second);

    return pts;
}
/** End Convex **/

vector<pt> poly;
vector<line> lines;
vector<array<pt, 2>> origPoints;
vector<line> convertLines(vector<line> &lines) {
    vector<line> borders;
    for (int i = 0; i < lines.size(); i++) {
        array<pt, 2> newPoints = {lines[i].proj(origPoints[i][0]), lines[i].proj(origPoints[i][1])};
        line nb = line{newPoints[0], newPoints[1]};
        borders.push_back(nb);
    }
    return borders;
}
line shiftLine(line l, double x) {
    pt pp = perp(l.v);
    pp = pp / abs(pp);
    pp = pp * x;
    return l.translate(pp);
}
double binSearch(double l, double r, int iter) {
    double mid = (l + r) / 2.0;
    if (iter == 50)
        return mid;
    vector<line> cur;
    for (auto i : lines) {
        cur.push_back(shiftLine(i, mid));
    }
    auto res = convertLines(cur);
    double area = areaPolygon(halfPlaneIntersection(res));
    if (abs(area) <= 0) {
        return binSearch(l, mid, iter + 1);
    } else {
        return binSearch(mid, r, iter + 1);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.setf(ios::fixed);
    cout.precision(20);
    cin >> N;
    for (int i = 0; i < N; i++) {
        pt x;
        cin >> x;
        poly.push_back(x);
    }
    for (int i = 0; i < N; i++) {
        lines.push_back(line(poly[i], poly[(i + 1) % N]));
        origPoints.push_back({poly[i], poly[(i + 1) % N]});
    }
    cout << fixed << setprecision(20) << binSearch(0, 1e7, 0) << endl;
}

vector<int> Manacher(string s, bool parity) {
    int n = s.size(), z = parity, l = 0, r = 0;
    vector<int> ret(n - !z, 0);
    for (int i = 0; i < n - !z; ++i) {
        if (i + !z < r)
            ret[i] = min(r - i, ret[l + r - i - !z]);
        int L = i - ret[i] + !z, R = i + ret[i];
        while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1])
            ++ret[i], --L, ++R;
        if (R > r)
            l = L, r = R;
    }
    return ret;
}