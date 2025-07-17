import sys
a = list(map(int, sys.stdin.readline().split()))
b = sorted(a)
d = b[2]
while True :
    ct = 0
    for i in b:
        if d % i == 0:
            ct +=1
    if ct >= 3:
        print(d)
        break
    else:
        d += 1