#include <bits/stdc++.h>

using namespace std;

int A, B, A1, B1, A2, B2;

bool isPossible(int a1, int b1, int a2, int b2) {
    if ((a1 + a2 <= A and max(b1, b2) <= B) || (max(a1, a2) <= A and b1 + b2 <= B))
        return true;
    return false;
}

int main() {
    cin >> A >> B;
    cin >> A1 >> B1;
    cin >> A2 >> B2;
    if (isPossible(A1, B1, A2, B2) || isPossible(B1, A1, A2, B2) || isPossible(A1, B1, B2, A2) ||
        isPossible(B1, A1, B2, A2)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}