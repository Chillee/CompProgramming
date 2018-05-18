from collections import defaultdict
from math import factorial

ans = {k: defaultdict(int) for k in range(1, 82 + 1)}
ans[1][0], ans[1][1], ans[2][1], ans[2][2] = 1, 1, 2, 1
for i in range(3, 82 + 1):
    for j in range(0, 82):
        ans[i][j + 1] += ans[i - 1][j]
        ans[i][j + 1] += ans[i - 2][j]


def soln_one(win_prob):
    result = 0
    for k, v in ans[82].items():
        result += v * (win_prob**k) * ((1 - win_prob)**(82 - k))
    return result


def nCr(n, r):
    if r > n:
        return 0
    return factorial(n) / factorial(r) / factorial(n - r)


def soln_two(win_prob):
    total = 0
    for i in range(81):
        for j in range(i + 1):
            total += nCr(i - j, j) * win_prob ** (i - j) * (1-win_prob) ** (j)
    return 1 - (total * ((1-win_prob) ** 2))

print("Solution 1: ", soln_one(.8))
print("Solution 2: ", soln_two(.8))


def bin_search(l, h, soln_f, depth=0):
    if depth > 50:
        return l
    mid = (l + h) / 2
    result = soln_f(mid)
    if result > .5:
        return bin_search(l, mid, soln_f, depth + 1)
    else:
        return bin_search(mid, h, soln_f, depth + 1)

print("Necessary win probably for 50%, Solution 1: ", bin_search(0, 1, soln_one))
print("Necessary win probably for 50%, Solution 1: ", bin_search(0, 1, soln_two))
