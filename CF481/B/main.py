N = input()
S = input()
count = 0
while "xxx" in S:
    count += 1
    idx = S.index("xxx")
    S = S[:idx] + S[idx+1:]
print(count)
