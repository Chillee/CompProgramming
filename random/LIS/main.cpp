#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> A = {1, 2, 5, 7, 3, 4, 3, 3, 4, 4};
    vector<int> ans;
    for (auto x : A) {
        auto it = lower_bound(ans.begin(), ans.end(), x);
        if (it == ans.end())
            ans.push_back(x);
        else
            *it = x;
    }
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << endl;
}