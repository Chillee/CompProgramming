vector<int> primes;
void calcPrimes() {
    const int S = round(sqrt(MAXPR));

    vector<bool> sieve(S + 1, true);
    vector<int> curPrimes, startIdxs;
    for (int i = 3; i <= S; i += 2) {
        if (sieve[i]) {
            curPrimes.push_back(i);
            startIdxs.push_back((i * i - 1) / 2);
            for (int j = i * i; j <= S; j += 2 * i)
                sieve[j] = false;
        }
    }

    primes.push_back(2);
    vector<char> block(S);
    int high = (MAXPR - 1) / 2;
    for (int low = 0; low <= high; low += S) {
        fill(block.begin(), block.end(), true);
        for (int i = 0; i < curPrimes.size(); i++) {
            int p = curPrimes[i];
            int idx = startIdxs[i];
            for (; idx < S; idx += p)
                block[idx] = false;
            startIdxs[i] = idx - S;
        }
        if (low == 0)
            block[0] = false;
        for (int i = 0; i < S && low + i <= high; i++) {
            if (block[i])
                primes.push_back((low + i) * 2 + 1);
        }
    };
}