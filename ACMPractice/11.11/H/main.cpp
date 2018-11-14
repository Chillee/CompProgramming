#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;

bool isPrime[MAXN];
vector<int> primes;

int X;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill(begin(isPrime), end(isPrime), true);
    cin >> X;
    isPrime[1] = false;
    for (int i = 2; i <= MAXN / 2; i++) {
        if (!isPrime[i])
            continue;
        primes.push_back(i);
        for (int j = 2 * i; j <= MAXN; j += i)
            isPrime[j] = false;
    }
    int cnt = 0;
    while (X >= 4) {
        for (int p : primes) {
            if (isPrime[X - p]) {
                X -= 2 * p;
                cnt++;
                break;
            }
        }
    }
    cout << cnt << endl;
}