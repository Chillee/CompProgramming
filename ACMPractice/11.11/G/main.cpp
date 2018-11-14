#include <bits/stdc++.h>

using namespace std;

int X, Y, X1, Y1, X2, Y2;
int sq(int x) { return x * x; }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> X >> Y >> X1 >> Y1 >> X2 >> Y2;
    double ans;
    if (X <= X1 && Y <= Y1)
        ans = sqrt(sq(X1 - X) + sq(Y1 - Y));
    else if (X1 <= X && X <= X2 && Y <= Y1)
        ans = Y1 - Y;
    else if (X2 <= X1 && Y <= Y1)
        ans = sqrt(sq(X - X2) + sq(Y - Y1));
    else if (X2 <= X && Y1 <= Y && Y <= Y2)
        ans = X - X2;
    else if (X2 <= X && Y2 <= Y)
        ans = sqrt(sq(X - X2) + sq(Y - Y2));
    else if (X1 <= X && X <= X2 && Y2 <= Y)
        ans = Y - Y2;
    else if (X <= X1 && Y2 <= Y)
        ans = sqrt(sq(X1 - X) + sq(Y - Y2));
    else if (X <= X1 && Y1 <= Y && Y <= Y2)
        ans = X1 - X;
    cout << fixed << setprecision(3) << ans << endl;
}