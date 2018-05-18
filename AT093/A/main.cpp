#include <bits/stdc++.h>

using namespace std;

int A[100005];
int N;

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    int sum = 0;
    for (int i = 1; i <= N + 1; i++) {
        sum += abs(A[i - 1] - A[i]);
    }
    for (int i = 1; i <= N; i++) {
        cout << sum - abs(A[i - 1] - A[i]) - abs(A[i + 1] - A[i]) + abs(A[i - 1] - A[i + 1]) << endl;
    }
}