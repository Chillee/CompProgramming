

def solution(A, E):
    alist = [[] for i in range(len(A))]
    for idx in range(0, len(E), 2):
        alist[E[idx] - 1].append(E[idx+1] - 1)
        alist[E[idx+1] - 1].append(E[idx] - 1)
    final = 0
    for i in range(len(A)):
        vis = set([i])
        def dfs(cur):
            if cur in vis:
                return 0
            vis.add(cur)
            res = 0
            for i in alist[cur]:
                if A[i] == A[cur]:
                    res = max(dfs(i), res)
            return res + 1
        results = [dfs(j) for j in alist[i] if A[j] == A[i]]
        results = sum(sorted(results)[-2:])
        final = max(final, results)
    return final


print(solution([3,2,1,4,5,1,1], [1,2,1,3,2,4,2,5,3,6,3,7]))