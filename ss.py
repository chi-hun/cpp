n = int(input())
for _ in range(n):
    a, b = map(int, input().split())
    a_1 = 1
    for i in range(a,0,-1):
        a_1 *= i
    b_1 = 1
    for i in range(b,b-a,-1):
        b_1 *= i
    print(b_1//a_1)