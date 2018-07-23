#include <bits/stdc++.h>
using namespace std;

#define long long long

template <class T> inline void MIN(T &a, T b) {
    if (a > b)
        a = b;
}
template <class T> inline void MAX(T &a, T b) {
    if (a < b)
        a = b;
}

int n, m;
vector<pair<int, int>> e;

void no() { exit(!printf("Impossible\n")); }

void test() {
    int N = min(n, 575);
    for (int i = 2; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (__gcd(i, j) == 1) {
                e.emplace_back(i, j);
            }
        }
    }
    if ((int)e.size() >= m) {
        printf("Possible\n");
        for (int i = 2; i <= n; i++) {
            printf("1 %d\n", i);
        }
        for (int i = 0; i < m; i++) {
            printf("%d %d\n", e[i].first, e[i].second);
        }
    } else {
        no();
    }
    // printf("%d edges with N = %d\n", ans, N);
}

int main() {

    scanf("%d %d", &n, &m);

    if (m < n - 1)
        no();
    m -= n - 1;

    test();
}