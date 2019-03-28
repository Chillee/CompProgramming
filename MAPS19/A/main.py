from fractions import Fraction
F, B = input().split()
F = int(F)
B = int(B)
Fs = [int(i) for i in input().split()]
Bs = [int(i) for i in input().split()]
vals = []
for i in Fs:
    for j in Bs:
        vals.append([Fraction(i, j), i, j])
vals = sorted(vals)
for i in vals:
    print(f"({i[1]},{i[2]})")
