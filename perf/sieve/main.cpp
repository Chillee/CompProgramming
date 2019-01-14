#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e8 + 5;
bool sieve[MAXN];
vector<int> primes;
void calc() {
    for (int i = 3; i < MAXN; i += 2) {
        if (!sieve[i])
            primes.push_back(i);
        for (int j = 0; j < primes.size() && i * primes[j] < MAXN; j++) {
            sieve[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}
bitset<MAXN> sieve2;
vector<int> primes2;
void calc2() {
    int i = 3;
    for (; i * i < MAXN; i += 2) {
        if (sieve2[i])
            continue;

        primes2.push_back(i);
        for (int j = i * i; j < MAXN; j += 2 * i)
            sieve2[j] = true;
    }
    while (i < MAXN) {
        if (!sieve2[i])
            primes2.push_back(i);
        i += 2;
    }
}
unsigned int prime[MAXN / 64];
#define gP(n) (prime[n >> 6] & (1 << ((n >> 1) & 31)))
#define rP(n) (prime[n >> 6] &= ~(1 << ((n >> 1) & 31)))
bool checkPrime(int x) { return (x & 1) && gP(x); }
vector<int> primes3;
void calc3() {
    memset(prime, -1, sizeof(prime));

    for (int i = 3; i * i < MAXN; i += 2)
        if (gP(i)) {
            for (unsigned int j = i * i; j < MAXN; j += 2 * i)
                rP(j);
        }
    for (int i = 2; i < MAXN; i++)
        if (checkPrime(i))
            primes3.push_back(i);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    clock_t begin;
    begin = clock();
    calc();
    cout << "sieve1: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes.size() << endl;
    begin = clock();
    calc2();
    cout << "sieve2: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes2.size() << endl;
    begin = clock();
    calc3();
    cout << "bitset: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes3.size() << endl;
}