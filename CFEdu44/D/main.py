import math

N, H = input().split(' ')
N = int(N)
H = int(H)
H -= 1

if H*(H+1)//2 > N:
    res = int(math.floor(0.5*(math.sqrt(8*N+1) - 1)))
    if res*(res+1)//2 == N:
        print(res)
    else:
        print(res+1)
else:
    res = int(math.floor(0.5*(math.sqrt(2*H**2 + 2*H+4*N+1)-2*H-1)))
    sm = (H+res)*(H+res+1) - H*(H+1)//2
    if N == sm:
        print(2*res + H)
    elif N - sm > H+res+1:
        print(2*res+H+2)
    else:
        print(2*res+H+1)
