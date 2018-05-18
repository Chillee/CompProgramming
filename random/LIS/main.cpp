#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> A = {1, 2, 5, 7, 3, 4, 3, 3, 4, 4};
    int prev[A.size()] = {0};
    map<int, int> dp;
    for (int i : A) {
        auto lb = dp.upper_bound(i);
        int val = -1;
        if (lb == dp.begin()) {
            val = 1;
        } else {
            lb--;
            val = lb->second + 1;
        }
        while (true) {
            auto ub = dp.lower_bound(i);
            if (ub != dp.end() && ub->second <= val) {
                dp.erase(ub);
            } else {
                break;
            }
        }
        dp[i] = val;
    }
    for (auto i : dp) {
        cout << i.first << ' ' << i.second << endl;
    }
}