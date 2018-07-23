#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // vector<int> test;
    // test.reserve(32768);
    // test.max_load_factor(.25);
    clock_t begin = clock();
    unordered_map<int, int> test;
    for (int t = 0; t < 1e6; t++) {
        test[t] = t;
    }
    cout << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}