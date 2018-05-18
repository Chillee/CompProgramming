while True:
    s, n = input().split()
    if s == '0' and n == '0':
        break
    marks = 0
    if s[:2] == '0x':
        s = int(s, 16)
    elif s[0] == '0':
        s = int(s, 8)
    else:
        s = int(s)
    n = int(n)
    correct_val = None
    next_val = None
    for _ in range(n):
        op, val = input().split()
        val = int(val)
        if op == 'i++':
            correct_val = s
            next_val = s+1
            s = val + 1
        elif op == 'i--':
            correct_val = s
            next_val = s-1
            s = val - 1
        elif op == '++i':
            correct_val = s+1
            next_val = s+1
            s = val
        elif op == '--i':
            correct_val = s-1
            next_val = s-1
            s = val
        elif op == 'i':
            correct_val = s
            next_val = s
            s = val
        if val == correct_val:
            marks += 1
    print(marks)
