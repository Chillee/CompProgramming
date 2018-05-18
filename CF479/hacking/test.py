
grams = {}
noc = int(input())
maxlen = int(-10e12)
s = input()
winner = ""
for i in range(noc-1):
    curr = s[i:i+2]
    grams[curr] = grams.get(curr, 0) + 1
    maxlen = max(maxlen, grams[curr])
    if maxlen == grams[curr]:
        winner = curr
print(winner)
