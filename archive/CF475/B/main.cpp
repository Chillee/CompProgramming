#include <bits/stdc++.h>

using namespace std;

int N, A, B, C, T;
int times[1005];
int main() {
    cin >> N >> A >> B >> C >> T;
    for (int i = 0; i < N; i++) {
        cin >> times[i];
    }
    int sum = 0;
    for (int i = 0; i < N; i++) {
        int timeDiff = T - times[i];
        sum += max(timeDiff * C - (timeDiff * B) + A, A);
    }
    cout << sum << endl;
}