#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
const ld PI = 3.1415926535897932384626;
const ld EPS = 1e-12;
typedef pair<ld, ld> pii;

vector<pii> A;
vector<pii> B;

bool isInside(pii pt, vector<pii> square) {
    return (pt.first >= square[0].first - EPS && pt.first <= square[2].first + EPS &&
            pt.second >= square[0].second - EPS && pt.second <= square[1].second + EPS);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < 4; i++) {
        int x, y;
        cin >> x >> y;
        A.push_back({x, y});
    }
    sort(A.begin(), A.end());
    for (int i = 0; i < 4; i++) {
        int x, y;
        cin >> x >> y;
        B.push_back({x, y});
    }
    pii midPoint = {0, 0};
    for (auto i : B) {
        midPoint.first += i.first;
        midPoint.second += i.second;
        if (isInside(i, A)) {
            cout << "YES" << endl;
            return 0;
        }
    }
    midPoint.first /= 4;
    midPoint.second /= 4;
    if (isInside(midPoint, A)) {
        cout << "YES" << endl;
        return 0;
    }
    for (auto &i : A) {
        ld newX = cos(PI / 4) * i.first - sin(PI / 4) * i.second;
        ld newY = sin(PI / 4) * i.first + cos(PI / 4) * i.second;
        i.first = newX;
        i.second = newY;
    }
    for (auto &i : B) {
        ld newX = cos(PI / 4) * i.first - sin(PI / 4) * i.second;
        ld newY = sin(PI / 4) * i.first + cos(PI / 4) * i.second;
        i.first = newX;
        i.second = newY;
    }
    sort(B.begin(), B.end());
    midPoint = {0, 0};
    for (auto i : A) {
        midPoint.first += i.first;
        midPoint.second += i.second;
        if (isInside(i, B)) {
            cout << "YES" << endl;
            return 0;
        }
    }
    midPoint.first /= 4;
    midPoint.second /= 4;
    if (isInside(midPoint, B)) {
        cout << "YES" << endl;
        return 0;
    }
    cout << "NO" << endl;
}