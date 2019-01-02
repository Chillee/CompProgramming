#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll egcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = egcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

ll N, M, X, Y, Vx, Vy;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> X >> Y >> Vx >> Vy;
    ll x0, y0;
    ll gcd = egcd(N * Vy, -M * Vx, x0, y0);
    ll c = X * Vy - Y * Vx;
    if (c % gcd != 0) {
        cout << -1 << endl;
        return 0;
    }
    ll mul = c / gcd;
    ll resX = x0 * mul;
    ll resY = y0 * mul;
    // cout << resX << ' ' << resY << endl;
    while (true) {
        if (Vx < 0 && resX > 0) {
            ll mult = (resX / (-M * Vx / gcd));
            if (mult * (-M * Vx / gcd) == resX) {
                resX -= (-M * Vx / gcd) * mult;
                resY += (N * Vy / gcd) * mult;
            } else {
                resX -= (-M * Vx / gcd) * (mult + 1);
                resY += (N * Vy / gcd) * (mult + 1);
            }
            break;
        } else if (Vx == 0 && resX <= 0) {
            ll mult = 0;
            resX -= (-M * Vx / gcd) * (mult + 1);
            resY += (N * Vy / gcd) * (mult + 1);
            break;
        } else if (Vx > 0 && resX <= 0) {
            ll mult = (resX / (-M * Vx / gcd));
            resX -= (-M * Vx / gcd) * (mult + 1);
            resY += (N * Vy / gcd) * (mult + 1);
            break;
        } else if (Vx > 0 && resX > -M * Vx / gcd) {
            ll mult = (resX / (-M * Vx / gcd));
            resX -= (-M * Vx / gcd) * mult;
            resY += (N * Vy / gcd) * mult;
            if (resX == 0) {
                resX += (-M * Vx / gcd);
                resY -= (N * Vy / gcd);
            }
            break;
        } else if (Vx < 0 && resX < -(-M * Vx / gcd)) {
            resX -= (-M * Vx / gcd) * (resX / (-M * Vx / gcd));
            resY += (N * Vy / gcd) * (resY / (-N * Vy / gcd));
            if (resX == 0) {
                resX += (-M * Vx / gcd);
                resY -= (N * Vy / gcd);
            }
            break;
        } else {
            break;
        }
    }
    // cout << resX << ' ' << resY << endl;
    ll finalX, finalY;
    if (resX % 2 == 0) {
        finalX = 0;
    } else {
        finalX = N;
    }
    if (resY % 2 == 0) {
        finalY = 0;
    } else {
        finalY = M;
    }
    cout << finalX << ' ' << finalY << endl;
}