n = int(input())
arr = list(map(int, input().split()))
serch = int(input())
re = 0
for i in range(n):
    if arr[i] == serch:
        re += 1
print(re)