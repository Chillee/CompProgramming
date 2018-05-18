#include <bits/stdc++.h>

using namespace std;

int N;
int main() {
    cin >> N;
    int W = ceil(sqrt(float(N)));
    int H = ceil(N / (W + 0.0));
    cout << 2 * W + 2 * H << endl;
}