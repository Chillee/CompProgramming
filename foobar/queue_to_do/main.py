def answer(start, length):
    def preXor(n):
        if n % 4 == 0:
            return n
        elif n % 4 == 1:
            return 1
        elif n % 4 == 2:
            return n+1
        elif n % 4 == 3:
            return 0
    result = 0
    cur = start
    curL = length
    while curL > 0:
        result ^= preXor(cur+curL - 1) ^ preXor(cur-1)
        cur += length
        curL -= 1
    return result

print(answer(17, 4))