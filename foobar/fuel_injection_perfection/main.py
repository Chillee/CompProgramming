def answer(n):
    n = float(n)
    cache = {}

    def dfs(cur):
        if cur in cache:
            return cache[cur]
        if cur == 1:
            return 0
        elif cur < 1:
            return 1e9
        elif cur % 2 == 0:
            cache[cur] = dfs(cur / 2) + 1
        elif cur % 2 == 1:
            cache[cur] = dfs((cur + 1) / 2) + 2
            cache[cur] = min(cache[cur], dfs((cur - 1) / 2) + 2)
        return cache[cur]
    res = dfs(n)
    return res