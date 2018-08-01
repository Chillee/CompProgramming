#include <bits/stdc++.h>

using namespace std;

int main() {
    // Generating subsets
    int N = 4;
    for (int i = (1 << N) - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            if (i & (1 << j)) {
                cout << "1";
            } else {
                cout << "0";
            }
        }
        cout << endl;
    }
    // Generating permutations
    vector<int> permutation{0, 1, 2, 3};
    do {
        for (auto i : permutation) {
            cout << i;
        }
        cout << endl;
    } while (next_permutation(permutation.begin(), permutation.end()));
}