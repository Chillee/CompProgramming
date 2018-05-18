#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> a = {5, 10};
    auto lb = lower_bound(a.begin(), a.end(), 4);
    // lb--;
    if (lb == a.begin()) {
        cout << "at beginning" << endl;
    }
    if (lb == a.end()) {
        cout << "at end" << endl;
    }
    cout << *lb << endl;
}