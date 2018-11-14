#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    int operator()(array<int, 6> x) const {
        int cur = 1;
        for (int i = 0; i < 6; i++) {
            cur = hash_combine(hash_f(x[i]), hash_f(cur));
        }
        return cur;
    }
};
gp_hash_table<array<int, 6>, int, chash> cnts;
int N;
vector<array<int, 6>> allDice;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        array<int, 6> dice;
        for (int j = 0; j < 6; j++) {
            int t;
            cin >> t;
            dice[j] = t;
        }
        array<int, 6> minDice = {10, 10, 10, 10, 10, 10};
        array<int, 4> mapping[6];
        mapping[0] = {2, 3, 4, 5};
        mapping[1] = {2, 3, 5, 4};
        mapping[2] = {5, 4, 1, 0};
        mapping[3] = {5, 4, 0, 1};
        mapping[4] = {2, 3, 1, 0};
        mapping[5] = {2, 3, 0, 1};
        for (int j = 0; j < 6; j++) {
            array<int, 4> rotFaces = {mapping[j][0], mapping[j][1], mapping[j][2], mapping[j][3]};
            array<int, 4> rots[4];
            rots[0] = {0, 1, 2, 3};
            rots[1] = {1, 0, 3, 2};
            rots[2] = {2, 3, 1, 0};
            rots[3] = {3, 2, 0, 1};
            for (auto k : rots) {
                array<int, 6> curDice;
                curDice[0] = j;
                curDice[1] = j ^ 1;
                curDice[2] = rotFaces[k[0]];
                curDice[3] = rotFaces[k[1]];
                curDice[4] = rotFaces[k[2]];
                curDice[5] = rotFaces[k[3]];
                for (auto &l : curDice) {
                    l = dice[l];
                }
                minDice = min(minDice, curDice);
            }
        }
        allDice.push_back(minDice);
    };
    for (auto i : allDice) {
        // for (int j = 0; j < 3; j++) {
        //     cout << "(";
        //     for (int k = 0; k < 2; k++)
        //         cout << i[j][k] << ",";
        //     cout << ") ";
        // }
        // cout << endl;
        cnts[i]++;
    }
    int ans = 0;
    for (auto i : cnts) {
        ans = max(ans, i.second);
    }
    cout << ans << endl;
}