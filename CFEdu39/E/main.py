from sys import stdin, stdout

# n = int(input())
f = open('input.txt', 'r')
n = int(f.readline())


def haspalindrome(n):
    s = str(s)
    counts = [0 for _ in range(10)]
    for i in s:
        counts[ord(i) - ord('0')] += 1
    for i in counts:
        if i % 2 == 1:
            return False
    return True


for _ in range(n):
    s = int(f.readline())
    # s = int(input())
    s -= 1
    s = list(str(s))
    if len(s) % 2 == 1:
        s = list("9"*(len(s)-1))
    while True:
        old_s = s[:]

        def oddcnt():
            return sum([i % 2 for i in counts])
        cur_idx = len(s)
        counts = [0 for _ in range(10)]
        for idx, i in enumerate(s):
            counts[int(i)] += 1
            if oddcnt() > len(s) - idx - 1:
                cur_idx = idx
                break

        # print(f'cur_idx {cur_idx}')
        counts = [0 for _ in range(10)]
        for i in s[:cur_idx]:
            counts[int(i)] += 1
        success = True
        is_always_higher = False
        for idx in range(cur_idx, len(s)):
            break
            cur = s[idx]
            # print(idx, cur, counts)
            found_val = False
            for i in range(9 if is_always_higher else int(cur), -1, -1):
                if counts[i] % 2 == 1:
                    if i != int(cur):
                        is_always_higher = True
                    s[idx] = str(i)
                    counts[i] += 1
                    found_val = True
                    break
            if not found_val:
                if sum([i % 2 for i in counts]) == 0:
                    counts[int(cur)] += 1
                    continue
                else:
                    success = False
                    break

        counts = [0 for _ in range(10)]
        for i in s:
            counts[int(i)] += 1
        # print(counts)
        for i in counts:
            if i % 2 == 1:
                success = False
        if not success:
            if int(s[0]) == 1:
                s = list("9"*(len(s)-2))
            else:

                s[0] = str(int(s[0])-1)
                for i in range(1, len(s)):
                    s[i] = '9'
                s[-1] = s[0]
                stdout.write(''.join(s))
                break
        else:
            stdout.write(''.join(s))
            break

        # print("---")
