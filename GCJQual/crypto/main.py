from math import gcd
T = int(input())
for _ in range(T):
    N, L = input().split()
    N = int(N)
    L = int(L)
    vals = input().split()
    vals = [int(i) for i in vals]
    primes = []
    for i in range(L-1):
        primes.append(gcd(vals[i], vals[i+1]))
    primes.insert(0, vals[0]//primes[0])
    primes.append(vals[-1]//primes[-1])
    ans = primes[:]
    primes = list(set(primes))
    res = ""
    for i in ans:
        for j in range(26):
            if i == primes[j]:
                res += chr(ord('A') + j)
    print(res)
