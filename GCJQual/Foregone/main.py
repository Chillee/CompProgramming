T = int(input())
for t in range(T):
    N = input().strip()
    a = 0
    b = 0
    for i in N:
        if i == '4':
            a *= 10
            a += 2
            b *= 10
            b += 2
        else:
            a *= 10
            a += int(i)
            b *= 10
    print("Case #" + str(t+1)+": " + str(a)+" " + str(b))
