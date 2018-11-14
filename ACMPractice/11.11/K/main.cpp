#include <bits/stdc++.h>

using namespace std;

const int MAXB = 12;
const int MAXR = 15;
double dpM[1 << MAXB][MAXR];
double dpm[1 << MAXB][MAXR];
double p(int i) {
    if (i <= 1)
        return 0;
    if (i <= 7)
        return (i - 1) / 36.0;
    return (13 - i) / 36.0;
}
void genSubsets(int val, int idx, int sum, vector<int> &x, vector<int> &cur, vector<vector<int>> &res) {
    // cout << idx << ' ' << sum << endl;
    if (val == sum) {
        res.push_back(cur);
        return;
    }
    if (idx >= x.size() || sum > val) {
        return;
    }
    for (int j = idx; j < x.size(); j++) {
        cur.push_back(x[j]);
        genSubsets(val, j + 1, sum + x[j], x, cur, res);
        cur.pop_back();
    }
}

array<vector<int>, 2> solve(bitset<MAXB> mask, int roll) {
    // if (roll > 12) return
    // cout << dpM[mask.to_ulong()][roll] << endl;
    if (dpM[mask.to_ulong()][roll] != -1)
        return {vector<int>(), vector<int>()};
    vector<int> num;
    for (int i = 0; i < mask.size(); i++) {
        if (mask[i])
            num.push_back(i + 1);
    }
    vector<int> t = vector<int>();
    vector<vector<int>> subsets;
    genSubsets(roll, 0, 0, num, t, subsets);
    // cout << "val: " << roll << endl;
    // cout << subsets.size() << endl;
    if (subsets.empty()) {
        int cur = 0;
        for (auto i : num) {
            cur *= 10;
            cur += i;
        }
        dpM[mask.to_ulong()][roll] = cur;
        dpm[mask.to_ulong()][roll] = cur;
        return {vector<int>(), vector<int>()};
    }
    // cout << mask << ' ' << roll << endl;
    // cout << "subsets: " << endl;
    // for (auto i : subsets) {
    //     for (auto j : i) {
    //         cout << j << ' ';
    //     }
    //     cout << endl;
    // }
    double lo = 1e9, hi = -1;
    vector<int> tHi = vector<int>(), tLo = vector<int>();
    for (auto t : subsets) {
        double resm = 0, resM = 0;
        for (auto i : t) {
            assert(mask[i - 1]);
            mask[i - 1] = 0;
        }
        for (int i = 2; i <= 12; i++) {
            // cout << "i: " << i << endl;
            solve(mask, i);
            // cout << "DONE" << endl;
            resm += p(i) * dpm[mask.to_ulong()][i];
            resM += p(i) * dpM[mask.to_ulong()][i];
        }
        if (lo > resm) {
            lo = resm;
            tLo = t;
        }
        if (hi < resM) {
            hi = resM;
            tHi = t;
        }
        for (auto i : t) {
            assert(!mask[i - 1]);
            mask[i - 1] = 1;
        }
    }
    dpM[mask.to_ulong()][roll] = hi;
    dpm[mask.to_ulong()][roll] = lo;
    return {tHi, tLo};
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < 1 << MAXB; i++) {
        for (int j = 0; j < MAXR; j++) {
            dpM[i][j] = -1;
            dpm[i][j] = -1;
        }
    }
    // for (int i = 0; i <= 12; i++) {
    //     cout << p(i) << ' ';
    // }
    // cout << endl;
    // return 0;
    int A, B;
    string state;
    cin >> state >> A >> B;
    bitset<MAXB> mask;
    for (auto i : state) {
        mask[i - '1'] = 1;
    }
    int roll = A + B;
    auto res = solve(mask, roll);
    if (res[1].empty()) {
        cout << -1 << ' ';
    } else {
        for (auto i : res[1])
            cout << i;
        cout << ' ';
    }
    cout << fixed << setprecision(5) << dpm[mask.to_ulong()][roll] << endl;
    if (res[0].empty()) {
        cout << -1 << ' ';
    } else {
        for (auto i : res[0])
            cout << i;
        cout << ' ';
    }
    cout << fixed << setprecision(5) << dpM[mask.to_ulong()][roll] << endl;
}