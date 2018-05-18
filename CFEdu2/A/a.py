s = input()
words = s.replace(',', ';').split(';')
a = []
b = []
for i in words:
    try:
        int(i)
        if len(str(int(i))) != len(i):
            raise ValueError
        a.append(i)
    except:
        b.append(i)

if len(a) > 0:
    print('"'+','.join(a)+'"')
else:
    print('-')
if len(b) > 0:
    print('"'+','.join(b)+'"')
else:
    print('-')