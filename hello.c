// 7 while
#include <stdio.h>

int main() {
    int n;
    char ss = ' ';
    char st = '*';
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i;  j++) {
            printf("%c", st);
        }
        printf("\n");
    }
    return 0;
}