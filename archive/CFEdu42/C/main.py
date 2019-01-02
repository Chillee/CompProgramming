from collections import defaultdict

N = input().strip()
squares = [str(i**2) for i in range(1, 45000)][::-1]

for i in squares:
    is_good = True
    cur_idx = 0
    for j in N:
        if j == i[cur_idx]:
            cur_idx += 1
            if cur_idx >= len(i):
                break
    if cur_idx == len(i):
        print(len(N) - len(i))
        exit(0)
print(-1)
