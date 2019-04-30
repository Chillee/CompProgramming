from math import gcd
T, W, B = [int(i) for i in input().split()]
wbgcd = gcd(W, B)
wblcm = B*W//wbgcd
numOcc = T//wblcm
num = numOcc*min(W, B)
mxVal = numOcc*wblcm
num += min(T+1-mxVal, min(W,B))
denom = T
num -= 1
print(str(num//gcd(num, denom)) + "/"+str(denom//gcd(num, denom)))
