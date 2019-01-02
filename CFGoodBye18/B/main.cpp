#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    int operator()(array<int, 2> x) const { return hash_combine(hash_f(x[0]), hash_f(x[1])) ^ RANDOM; }
};
const int MAXN = 1005;
int N;
array<int, 2> obelisks[MAXN];
array<int, 2> clues[MAXN];
gp_hash_table<array<int, 2>, int, chash> cnt;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> obelisks[i][0] >> obelisks[i][1];
    }
    for (int i = 0; i < N; i++)
        cin >> clues[i][0] >> clues[i][1];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            array<int, 2> cur = {obelisks[i][0] + clues[j][0], obelisks[i][1] + clues[j][1]};
            cnt[cur]++;
        }
    }
    for (auto i : cnt) {
        if (i.second == N) {
            cout << i.first[0] << " " << i.first[1] << endl;
            return 0;
        }
    }
}