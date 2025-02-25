"""
Other part writen in c++
is avaliable in file path
C:/Users/Magshimim/source/repos/IbmChallangeAttempt
"""

N = 4

file = open(f"FILE_PATH/N={N}.txt", "r")
s = file.read()
s = s.split('\n')[:-1]

k = [[] for _ in range(len(s)//(N+1) + 1)]
for i in range(len(s)):
    if i % (N+1) != N:
        k[i//(N+1)].append(s[i])
k = k[:-1]

for i in range(len(k)):
    for j in range(len(k[0])):
        k[i][j] = [int(n) for n in k[i][j].split(' ')[:-1]]


def toNum(A: list):
    sum = 0
    for i in range(len(A)):
        sum *= 10
        sum += A[i]
    return sum


def score(sq):
    N = len(sq)
    K = []
    for i in range(N):
        A = []
        for j in range(N):
            A.append(sq[i][j])
        K.append(toNum(A))

    for i in range(N):
        A = []
        for j in range(N):
            A.append(sq[j][i])
        K.append(toNum(A))

    A1, A2 = [], []
    for i in range(N):
        A1.append(sq[i][i])
        A2.append(sq[i][N-i-1])
    K.append(toNum(A1))
    K.append(toNum(A2))

    K = list(set(K))
    freq = [0]*10
    for p in K:
        for c in str(p):
            freq[int(c)] += 1

    sum = 0
    for f in freq:
        sum += f*(f-1)/2
    return int(sum)


def printsq(sq):
    for v in sq:
        print(v)
    print()




k2 = []
for sq in k:
    k2.append((score(sq), sq))
k2.sort()

print(str(k2[0][0]) + ":")
printsq(k2[0][1])

print(str(k2[-1][0]) + ":")
printsq(k2[-1][1])

# for score, sq in k2:
#     print(str(score) + ":")
#     printsq(sq)
