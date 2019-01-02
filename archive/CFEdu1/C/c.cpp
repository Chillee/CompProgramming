#include <bits/stdc++.h>

using namespace std;

typedef pair<long double, long double> pii;
typedef pair<int, pii> piii;
const long double PI = 3.141592653589793238462643383279502884197;
int N;
vector<piii> pts;

bool polar_cmp(piii a, piii b) {
    return atan2(a.second.second, a.second.first) > atan2(b.second.second, b.second.first);
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        long double x, y;
        cin >> x >> y;
        pts.push_back(piii(i, pii(1.0 * x, 1.0 * y)));
    }
    sort(pts.begin(), pts.end(), polar_cmp);
    long double mn = 100000;
    int res_a, res_b;
    for (int i = 0; i < pts.size(); i++) {
        pii a = pts[i].second;
        pii b = pts[(i + 1) % pts.size()].second;
        long double t = abs(atan2(a.second, a.first) - atan2(b.second, b.first));
        long double diff = min(t, 2 * PI - t);

        if (diff < mn) {
            mn = diff;
            res_a = pts[i].first;
            res_b = pts[(i + 1) % pts.size()].first;
        }
    }
    cout << res_a + 1 << ' ' << res_b + 1 << endl;
}