import random
f = open('input.txt', 'w')
f.write("1000 1000000000\n")
for i in range(1000):
    f.write(f"{random.randrange(-1000, 1000)}\n")
f.close()
