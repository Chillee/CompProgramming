from collections import defaultdict

s = input()
d = defaultdict(int)
for i in s:
    d[i] += 1

if len(s) < 4:
    print("No")
    exit()

vals = sorted(d.values())
if len(vals) == 1:
    print("No")
elif len(vals) == 2:
    if vals[0] == 1:
        print("No")
    else:
        print("Yes")
elif len(vals) == 3:
    print("Yes")
elif len(vals) == 4:
    print("Yes")
elif len(vals) > 4:
    print("No")
