#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e8 + 5;
bool sieve[MAXN];
vector<int> primes;
void calc() {
    for (int i = 3; i < MAXN; i += 2) {
        if (!sieve[i / 2 + 1])
            primes.push_back(i);
        for (int j = 0; j < primes.size() && i * primes[j] < MAXN; j++) {
            sieve[primes[j] * i / 2 + 1] = true;
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

const int MAX_PR = MAXN;
bitset<MAX_PR> isprime;
vector<int> primes4;
void calc4(int lim) {
    isprime.set();
    isprime[0] = isprime[1] = 0;
    for (int i = 4; i < lim; i += 2)
        isprime[i] = 0;
    for (int i = 3; i * i < lim; i += 2)
        if (isprime[i])
            for (int j = i * i; j < lim; j += i * 2)
                isprime[j] = 0;
    vector<int> pr;
    for (int i = 2; i < lim; i++)
        if (isprime[i])
            primes4.push_back(i);
    return;
}

int sieve5[MAXN];
vector<int> primes5;
int itr2 = 0;
void calc5() {
    for (int i = 3; i < MAXN; i += 2) {
        if (!sieve5[i])
            primes5.push_back(i);
        for (int j = 0; j < primes5.size() && i * primes5[j] < MAXN; j++) {
            sieve5[primes5[j] * i] = primes5[j];
            if (primes5[j] == sieve5[i])
                break;
        }
    }
}
vector<int> primes6;
void calc6() {
    int n = MAXN;
    const int S = 30000;

    int nsqrt = round(sqrt(n));

    vector<char> is_prime(nsqrt + 1, true);
    vector<int> primes, start_indices;
    for (int i = 3; i <= nsqrt; i += 2) {
        if (is_prime[i]) {
            primes.push_back(i);
            start_indices.push_back((i * i - 1) / 2);
            for (int j = i * i; j <= nsqrt; j += 2 * i)
                is_prime[j] = false;
        }
    }

    primes6.push_back(2);
    vector<char> block(S);
    int high = (n - 1) / 2;
    for (int low = 0; low <= high; low += S) {
        fill(block.begin(), block.end(), true);
        for (auto i = 0u; i < primes.size(); i++) {
            int p = primes[i];
            int idx = start_indices[i];
            for (; idx < S; idx += p)
                block[idx] = false;
            start_indices[i] = idx - S;
        }
        if (low == 0)
            block[0] = false;
        for (int i = 0; i < S && low + i <= high; i++) {
            if (block[i])
                primes6.push_back((low + i) * 2 + 1);
        }
    };
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    clock_t begin;
    begin = clock();
    calc2();
    cout << "nonlinear sieve: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes2.size() << endl;
    begin = clock();
    calc3();
    cout << "bitset: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes3.size() << endl;
    begin = clock();
    calc4(MAXN);
    cout << "kth: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes4.size() << endl;
    begin = clock();
    calc5();
    cout << "linear sieve v2: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes5.size() << endl;
    begin = clock();
    calc6();
    cout << "jakube: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes6.size() << endl;
    begin = clock();
    calc();
    cout << "linear sieve: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes.size() << endl;
}