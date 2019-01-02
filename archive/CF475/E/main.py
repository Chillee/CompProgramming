import math

MAXN = int(2e5 + 5)
N = 0
# ll W[MAXN], H[MAXN], C[MAXN];
W = [0 for i in range(MAXN)]
H = [0 for i in range(MAXN)]
C = [0 for i in range(MAXN)]


def lcm(a, b):
    return a*b/math.gcd(a, b)


N = int(input())
minC = 1 << 60
for i in range(N):
    w, h, c = input().split()
    w, h, c = int(w), int(h), int(c)
    W[i] = w
    H[i] = h
    C[i] = c
    minC = min(minC, c)
curLcm = W[0]
for i in range(1, N):
    curLcm = lcm(curLcm, W[i])

for i in range(0, N):
    print(C[i]*W[i])
    if (C[i]*W[i]) % curLcm != 0:
        print(0)
        exit(0)
    C[i] = C[i] * W[i] / curLcm

curGcd = C[0]
for i in range(1, N):
    print(C[i])
    curGcd = math.gcd(curGcd, C[i])
print(curGcd)
# ll ans = 0;
# for (ll i = 1; i * i <= curGcd; i++) {
#     if (i * i == curGcd && curGcd % i == 0) {
#         ans++;
#     } else if (curGcd % i == 0) {
#         ans += 2;
#     }
# }
# cout << ans << endl;
