// 11-1 
#include <stdio.h>
int main() {
  int a = 3;
  int b = 4;
  int c = 5;
  int *parr[3];
  parr[0] = &a;
  parr[1] = &b;
  parr[2] = &c;
  printf("%d \n", *(parr[0]+1));
  printf("%d \n", *(parr[1]));


  return 0;
}
