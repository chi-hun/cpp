// 11-1 
#include <stdio.h>
#include <math.h>

int main() {
    int ct = 2;
    int prime[1000];
    prime[0] = 2;
    prime[1] = 3;
    for (int i = 4; i < 1000000; i++) {
        // printf("%d \n", i);
        int flag = 0;
        for (int j = 0; j < ct; j++) {
            if (i % prime[j] == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            prime[ct] = i;
            ct++;
            printf("%d \n", i);
            if (ct == 1001) {
                break;
            }
        }
    }
    return 0;
}
