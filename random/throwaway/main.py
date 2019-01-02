from itertools import product
A = 2
B = 6
N = 3
X = 0
for i in range(N):
    X += A*(10**i)
for i in product([A, B], repeat=N):
    val = 0
    pw = 1
    for j in i[::-1]:
        val += j*pw
        pw *= 10
    # print(i, val % (2**N))
    # print(i, (val - X) % (2**N))
    # print()
