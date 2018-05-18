def dfs(C, F, s, t):
    stack = [s]
    paths = {s: []}
    if s == t:
        return paths[s]
    while(stack):
        u = stack.pop()
        for v in xrange(len(C)):
            if(C[u][v] - F[u][v] > 0) and v not in paths:
                paths[v] = paths[u] + [(u, v)]
                if v == t:
                    return paths[v]
                stack.append(v)
    return None


def max_flow(C, s, t):
    n = len(C)  # C is the capacity matrix
    F = [[0] * n for i in range(n)]
    path = dfs(C, F, s, t)
    while path != None:
        flow = min(C[u][v] - F[u][v] for u, v in path)
        for u, v in path:
            F[u][v] += flow
            F[v][u] -= flow
        path = dfs(C, F, s, t)
    return sum(F[s][i] for i in xrange(n))


def answer(entrances, exits, path):
    source = [0 for i in path[0]]
    for i in entrances:
        source[i] = sum(path[i])
    path = [source] + path + [[0 for i in path[0]]]
    for idx in range(len(path)):
        path[idx] = [0] + path[idx] + [0]
    for i in exits:
        path[i + 1][-1] = sum([path[idx][i + 1] for idx in range(len(path))])
    return max_flow(path, 0, len(path)-1)

print(answer([0],[3],[[0, 7, 0, 0], [0, 0, 6, 0], [0, 0, 0, 8], [9, 0, 0, 0]]))