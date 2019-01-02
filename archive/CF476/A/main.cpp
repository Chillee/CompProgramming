#include <bits/stdc++.h>

using namespace std;

int K, N, S, P;
int main() {
    cin >> K >> N >> S >> P;
    int sheetsPerPerson = (N + S - 1) / S;
    int numPacks = (sheetsPerPerson * K + P - 1) / P;
    cout << numPacks << endl;
}