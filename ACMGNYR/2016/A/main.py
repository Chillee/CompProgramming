P = int(input())
for _ in range(P):
    K, N = input().split()
    try:
        print(f'{K} {int(N, 8)} {int(N, 10)} {int(N,16)}')
    except:
        print(f'{K} 0 {int(N, 10)} {int(N,16)}')
