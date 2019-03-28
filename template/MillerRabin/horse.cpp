#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
const int bits = 10;
const ull po = 1 << bits;
ull modMul(ull a, ull b, ull &c) {
    ull x = a * (b & (po - 1)) % c;
    while ((b >>= bits) > 0) {
        a = (a << bits) % c;
        x += (a * (b & (po - 1))) % c;
    }
    return x % c;
}
ull binExp(ull b, ull pw, ull MOD) {
    if (pw == 0)
        return 1;
    return modMul(binExp(modMul(b, b, MOD), pw / 2, MOD), (pw & 1 ? b : 1), MOD);
};
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<ull> primes;
    const ull start = 1e11;
    for (ull i = start; i < start + 1e6; i++)
        if (isPrime(i))
            primes.push_back(i);
    cout << primes.size() << endl;
}