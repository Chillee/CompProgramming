from itertools import permutations
from math import factorial
val = []
N = 7
for i in permutations(range(1, N+1)):
    val += list(i)
sm = [0]
for i in val:
    sm.append(sm[-1]+i)
cnt = 0
for i in range(len(val)-N+1):
    if sm[i+N]-sm[i] == N*(N+1)//2:
        cnt += 1

print(factorial(N)*N - cnt)
