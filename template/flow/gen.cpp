#include <bits/stdc++.h>
using namespace std;

struct edg {
    int s, e, x;
};
vector<edg> v;

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N = 2000;
    if (argc > 1) {
        N = atoi(argv[1]);
    }
    for (int i = 1; i < N; i++) {
        v.push_back({i, i + 1, 100000000});
        v.push_back({i, N, 10000});
        for (int j = i + 3; j <= N; j++) {
            v.push_back({i, j, 1});
            v.push_back({j, i, 1});
        }
    }
    printf("%d %d\n", N, v.size());
    for (auto &i : v)
        printf("%d %d %d\n", i.s, i.e, i.x);
}