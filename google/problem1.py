
# you can write to stdout for debugging purposes, e.g.
# print "this is a debug message"

def solution(A, B):
    if A.find(B) != -1:
        return 1
    longA = (len(B)/len(A))*3*A
    idx = longA.find(B)
    if idx == -1:
        return -1
    lower_idx = idx-(idx % len(A))
    upper_idx = idx + len(B)
    upper_idx += (len(A) - upper_idx) % len(A)
    return (upper_idx - lower_idx)/len(A)
print(solution('aba', 'baabaabaabaabaa'))