
N, K, M, D = input().split(' ')
N = int(N)
K = int(K)
M = int(M)
D = int(D)
ans = -1
for d in range(1, D+1):
    numDivisors = K * (d - 1) + 1
    candiesPer = N // numDivisors
    if candiesPer == 0:
        continue
    if candiesPer > M:
        candiesPer = M
        if (N // (candiesPer * K) > D):
            candiesPer = N // (D * K)
    ans = max(ans, candiesPer * d)
# }
print(ans)
