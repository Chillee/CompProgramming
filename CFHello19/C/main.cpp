#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

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
    int operator()(int x) const { return hash_f(x) ^ RANDOM; }
};
int N;
string A[MAXN];
vector<int> lft, rght;
int corr;
gp_hash_table<int, int, chash> lftCnt, rghtCnt;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        int cur = 0, corrcur = 0;
        int mnL = 0;
        for (auto j : A[i]) {
            if (j == ')') {
                cur--;
                corrcur--;
            } else {
                cur++;
                corrcur++;
            }
            mnL = min(mnL, cur);
            corrcur = max(0, corrcur);
        }
        if (mnL == 0 && corrcur == 0) {
            corr++;
        } else if (mnL < 0 && corrcur == 0) {
            lft.push_back(mnL);
        } else if (mnL == 0 && corrcur > 0) {
            rght.push_back(corrcur);
        }
    }
    for (auto i : lft) {
        lftCnt[i]++;
    }
    for (auto i : rght) {
        rghtCnt[i]++;
    }
    int ans = 0;
    for (auto i : lftCnt) {
        ans += min(i.second, rghtCnt[-i.first]);
    }
    ans += corr / 2;
    cout << ans << endl;

    // cout << lft.size() << ' ' << rght.size() << ' ' << corr << endl;
}