N = int(input())
S = input().split(' ')
s = [tuple(sorted(tuple(set(i)))) for i in S]
print(len(set(s)))
