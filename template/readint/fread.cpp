#include <bits/stdc++.h>

using namespace std;

// struct GC {
//     char buf[1 << 16 | 1];
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
    static char c, s = 1;
    while (isspace(c = gc()))
        ;
    if (c == '-')
        s = -1, c = gc();
    for (a = c - '0'; isdigit(c = gc()); a = a * 10 + c - '0')
        ;
    if (s == -1)
        a = -a;
    read_int(b...);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    read_int(N);
    unsigned int x;
    for (int i = 0; i < N; i++) {
        read_int(x);
    }
    cout << x << endl;
}