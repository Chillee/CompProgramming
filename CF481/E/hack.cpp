#include <bits/stdc++.h>
//#include <ext/rope>

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")

#define endl "\n"
#define fi first
#define se second
#define pb push_back
#define last(s) (s)[int((s).size()) - 1]
#define prelast(s) (s)[int((s).size()) - 2]
#define all(a) (a).begin(), (a).end()
#define elif else if
#define left asdasd
#define next zaza
#define prev azaz
#define cclear cout << flush;
#define x0 kerker
#define time chas
#define y0 lolik
#define kchay                                                                                                          \
    ios_base::sync_with_stdio(0);                                                                                      \
    cin.tie(0);                                                                                                        \
    cout.tie(0);
#define files                                                                                                          \
    freopen("umbrella.in", "r", stdin);                                                                                \
    freopen("umbrella.out", "w", stdout);
#define ref svyazi
// #define int long long //
// #define real nihuya
using namespace std;
// using namespace __gnu_cxx;

using llong = long long;
using ld = long double;
using itn = int;
using ii = pair<int, int>;
using ull = unsigned long long;
using psi = pair<string, int>;
using ll = pair<llong, llong>;

const llong over999 = 1e9;
const ld over999ld = 1e18 + 1;
const llong md = 1e9 + 7;
const ld EPS = 1e-2;
const ld Pi = acos(-1);
const ld nich = 0;
const llong mnogo = 300;
// const int base = 1000*1000*1000;

/**/

llong n, w, a[1010], mx, mn, now;

int32_t main() {
    kchay;
    // files;
    cin >> n >> w;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        now += a[i];
        mn = min(mn, now);
        mx = max(mx, now);
    }

    mx -= mn;

    cout << max(w - mx + 1, 0LL);

    return 0;
}