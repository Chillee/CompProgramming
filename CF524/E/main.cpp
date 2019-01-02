#include <bits/stdc++.h>

using namespace std;

const int MAXN = 255;

array<vector<int>, 2> manacher(vector<int> &s) {
    int n = s.size();
    array<vector<int>, 2> p = {vector<int>(n), vector<int>(n)};
    for (int z = 0, l = 0, r = 0; z < 2; z++, l = 0, r = 0)
        for (int i = 0; i < n; i++) {
            if (i < r)
                p[z][i] = min(r - i + !z, p[z][l + r - i + !z]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1])
                p[z][i]++, L--, R++;
            if (R > r)
                l = L, r = R;
        }
    return p;
}

const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    int operator()(array<int, 26> x) const {
        int res = 1;
        for (int i = 0; i < 26; i++) {
            res = hash_combine(res, hash_f(x[i]));
        }
        return res;
    }
};

int N, M;
char grid[MAXN][MAXN];
array<int, 26> cnts[MAXN];
chash hashf;
bool isPal(array<int, 26> &x) {
    int odds = 0;
    for (int i = 0; i < 26; i++)
        odds += (x[i] % 2 == 1);

    return odds <= 1;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }
    int ans = 0;
    for (int lc = 0; lc < M; lc++) {
        for (int i = 0; i < MAXN; i++) {
            fill(cnts[i].begin(), cnts[i].end(), 0);
        }
        for (int rc = lc; rc < M; rc++) {
            for (int i = 0; i < N; i++) {
                cnts[i][grid[i][rc] - 'a']++;
            }
            vector<int> hashes;
            for (int i = 0; i < N; i++) {
                if (isPal(cnts[i])) {
                    hashes.push_back(hashf(cnts[i]));
                } else {
                    auto res = manacher(hashes);
                    for (auto i : res[1]) {
                        ans += i + 1;
                    }
                    for (auto i : res[0]) {
                        ans += i;
                    }
                    hashes.clear();
                }
            }
            auto res = manacher(hashes);
            for (auto i : res[1]) {
                ans += i + 1;
            }
            for (auto i : res[0]) {
                ans += i;
            }
            hashes.clear();
        }
    }
    cout << ans << endl;
}