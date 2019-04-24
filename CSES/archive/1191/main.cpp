#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 5e5 + 5;
int N;
ll K;
ll A[MAXN];
int nxt[MAXN];
int color[MAXN];
int cnt = 0;
int dfs(int cur, int clr) {
    while (color[cur] == 0) {
        color[cur] = clr;
        cnt++;
        cur = nxt[cur];
    }
    if (color[cur] != clr)
        return -1;
    int end = cur;
    int cnt = 0;
    cur = nxt[cur];
    while (cur != end) {
        cnt++;
        cur = nxt[cur];
    }
    return cnt + 1;
}
// struct GC {
//     char buf[16 * 1042 | 1];
//     int bc = 0, be = 0;
//     char operator()() {
//         if (bc >= be) {
//             be = fread(buf, 1, sizeof(buf) - 1, stdin);
//             buf[be] = bc = 0;
//         }
//         return buf[bc++];
//     }
// };
// GC gc;
char gc() {
#ifdef _WIN32
    return _getchar_nolock();
#else
    return getchar_unlocked();
#endif
}
void read_int() {}
template <class T, class... S> inline void read_int(T &a, S &... b) {
    char c, s = 1;
    while (isspace(c = gc()))
        ;
    for (a = c - '0'; isdigit(c = gc()); a = a * 10 + c - '0')
        ;
    a *= s;
    read_int(b...);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    read_int(N, K);
    // cin >> N >> K;
    ll sm = 0;
    for (int i = 0; i < N; i++) {
        read_int(A[i]);
        sm += A[i];
    }
    // if (sm <= K) {
    //     cout << 1 << endl;
    //     return 0;
    // }
    // cin >> A[i];
    ll csum = A[0];
    int r = 1;
    for (int l = 0; l < N; l++) {
        while (csum <= K) {
            csum += A[r];
            if (r == l) {
                cout << 1 << endl;
                return 0;
            }
            r++;
            r %= N;
        }
        nxt[l] = r == 0 ? N - 1 : r - 1;
        csum -= A[l];
    }
    int ans = MAXN;
    for (int i = 0; i < N; i++) {
        auto res = dfs(i, i + 1);
        if (res != -1)
            ans = min(ans, res);
        if (cnt >= N)
            break;
    }
    cout << ans << endl;
}