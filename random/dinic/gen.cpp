#include <bits/stdc++.h>
using namespace std;

struct edg {
    int s, e, x;
};
vector<edg> v;

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= 1998; i++) {
        v.push_back({i, i + 1, 100000000});
        v.push_back({i, 2000, 10000});
        for (int j = i + 3; j <= 1998; j++) {
            v.push_back({i, j, 1});
            v.push_back({j, i, 1});
        }
    }
    printf("2000 %d\n", v.size());
    for (auto &i : v)
        printf("%d %d %d\n", i.s, i.e, i.x);
}