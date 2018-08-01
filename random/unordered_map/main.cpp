#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    unordered_map<ll, ll> test;
    // test.reserve(32768);
    // test.max_load_factor(.25);
    clock_t begin = clock();
    for (int i = 0; i < 1e8; i++) {
        test[i >> 1] += test[i];
    }
    // cout << test[2] << endl;
}