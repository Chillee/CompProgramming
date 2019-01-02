from random import shuffle
from itertools import combinations
for N in range(6, 30, 6):
    for idx in range(6):
        moves = []
        # moves.append([i for i in range(N)])
        for i in range(0, N, 3):
            moves.append([(i) % N, (i+1) % N, (i+3) % N])
        for i in range(0, N, 3):
            moves.append([(i+1) % N, (i+2) % N, (i+4) % N])
        for i in range(0, N, 3):
            moves.append([(i+2) % N, (i+3) % N, (i+5) % N])
        cnt = [0]*N
        for m in moves:
            for j in m:
                cnt[j] += 1
        if max(cnt) > 3:
            print(cnt)
        success = False
        for l in range(len(moves)):
            if success:
                break
            for ms in combinations(moves, l):
                state = [0]*N
                for m in ms:
                    for i in m:
                        state[i] = 1-state[i]
                if sum(state) == 1 and state[idx] == 1:
                    print(
                        idx, N, [i if len(i) == 3 else -1 for i in ms])
                    # print(
                    #     idx, N, sorted(list(set([i[0] if len(i) == 3 else -1 for i in ms]))))
                    success = True
                    break
        if not success:
            print("NO")
