#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
double areaOfIntersection(ld x0, ld y0, ld r0, ld x1, ld y1, ld r1) {
    ld rr0 = r0 * r0;
    ld rr1 = r1 * r1;
    ld c = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
    ld phi = (acos((rr0 + (c * c) - rr1) / (2 * r0 * c))) * 2;
    ld theta = (acos((rr1 + (c * c) - rr0) / (2 * r1 * c))) * 2;
    ld area1 = 0.5 * theta * rr1 - 0.5 * rr1 * sin(theta);
    ld area2 = 0.5 * phi * rr0 - 0.5 * rr0 * sin(phi);
    if (isnan(area1) || isnan(area2)) {
        return 0;
    }
    return area1 + area2;
}

int main() {
    int x0, y0, r0, x1, y1, r1;
    cin >> x0 >> y0 >> r0;
    cin >> x1 >> y1 >> r1;
    cout << fixed;
    cout << setprecision(21);
    cout << areaOfIntersection(x0, y0, r0, x1, y1, r1);
}