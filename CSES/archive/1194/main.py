vis = []
B = []

N = 0


def isValid(r, c):
    return r >= 0 and c >= 0 and r < N and c < N


def dfs(r, c):
    if not isValid(r, c):
        return
    if vis[r][c]:
        return
    vis[r][c] = True
    dirs = [[1, 0], [-1, 0], [0, 1], [0, -1]]
    for d in dirs:
        dx, dy = d
        dfs(r+dx, r+dy)
