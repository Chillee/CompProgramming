#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define maxn 100005
using namespace std;
int n, ans = 2e9, t, a[maxn], b[maxn];
inline int read() {
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - 48, ch = getchar();
    return x;
}
void work(int x) {
    for (int i = 3; i <= n; ++i) {
        int y = abs(abs(a[i] - a[i - 1]) - x);
        if (y > 1)
            return;
        if (y > 0)
            ++t;
        a[i] = a[i - 1] + (a[2] - a[1]);
    }
    if (t < ans)
        ans = t;
}
int main() {
    n = read();
    for (int i = 1; i <= n; ++i)
        b[i] = read();
    for (int i = -1; i < 2; ++i)
        for (int j = -1; j < 2; ++j) {
            memcpy(a, b, sizeof(a));
            a[1] += i;
            a[2] += j;
            t = (i != 0) + (j != 0);
            work(abs(a[2] - a[1]));
            a[1] -= i;
            a[2] -= j;
        }
    printf("%d\n", ans == 2e9 ? -1 : ans);
    return 0;
}