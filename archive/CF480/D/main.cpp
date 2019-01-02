#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;
const int MAXFACTOR = 1e4 + 5;
int N;
int A[MAXN];
int res[MAXN];
vector<int> primes;
bool isPrime[MAXFACTOR];
int compress[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 2; j < MAXFACTOR; j++) {
            if (abs(A[i]) <= 1)
                continue;
            while (A[i] % (j * j) == 0) {
                A[i] = A[i] / (j * j);
            }
        }
    }
    map<int, int> earliest;
    for (int i = 0; i < N; i++) {
        if (earliest.count(A[i]) == 0) {
            earliest[A[i]] = i;
        }
        compress[i] = earliest[A[i]];
    }
    for (int l = 0; l < N; l++) {
        bool used[MAXN] = {0};
        bool onlyZero = true;
        int cnt = 0;
        for (int r = l; r < N; r++) {
            if (A[r] != 0) {
                onlyZero = false;
                if (!used[compress[r]]) {
                    cnt++;
                    used[compress[r]] = true;
                }
            }
            if (onlyZero) {
                res[1]++;
            } else {
                res[cnt]++;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        cout << res[i] << ' ';
    }
    cout << endl;
}