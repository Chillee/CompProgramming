#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> a = {};
    auto lb = lower_bound(a.begin(), a.end(), 6);
    if (lb != a.begin()) {
        lb--;
    }
    if (lb == a.begin()) {
        cout << "at beginning" << endl;
    }
    if (lb == a.end()) {
        cout << "at end" << endl;
    }
    cout << *lb << endl;
}