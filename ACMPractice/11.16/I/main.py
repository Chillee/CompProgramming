N, S = input().split()
N = int(N)
S = int(S)
vals = []
for _ in range(N):
    t, b = input().split()
    b = int(b)
    vals.append((b, t))
vals = sorted(vals)[::-1]
ans = []
for i in vals:
    if i[0] <= S:
        S -= i[0]
        ans.append(i[1])
if S == 0:
    print(len(ans))
    for i in ans:
        print(i)
else:
    print(0)
