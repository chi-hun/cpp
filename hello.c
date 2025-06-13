// 15-2 
#include <stdio.h>

void is_prime(int *arr);
int main() {
  char st[4];
  if (fgets(st, sizeof(st), stdin) != NULL) {
   printf("%s 맞나요?", st);
  } else{
    printf("xx");
  }

  char sts[4] = "ddd";
  printf("%s", sts);

  
  return 0;
}