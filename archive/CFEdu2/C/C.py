S = input()
letters = {}
for i in S:
    if i not in letters:
        letters[i] = 1
    else:
        letters[i] = letters[i] + 1

used_letters = sorted(letters.keys())
num_odd = 0
used_odd = False
for i in used_letters:
    if letters[i] % 2 == 1:
        for j in used_letters[::-1]:
            if letters[j]%2 ==1:
                letters[j] -= 1
                letters[i] += 1
                break


for i in used_letters:
    print(i*(letters[i]//2), end='')

for i in used_letters:
    if letters[i]%2 == 1:
        print(i, end='')

for i in used_letters[::-1]:
    print(i*(letters[i]//2), end='')
