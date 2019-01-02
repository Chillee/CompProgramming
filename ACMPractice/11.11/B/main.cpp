#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 1e7 + 5;
int phi[MAXN];
bool sieve[MAXN];
vector<int> primes;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 2; i < MAXN; i++) {
        if (!sieve[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; j < primes.size() && i * primes[j] < MAXN; j++) {
            sieve[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
    cout << phi[494] << endl;
}