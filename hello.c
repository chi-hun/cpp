// 15-2 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fuc.h"

int main(int argc, char **argv) {
  printf("받은 인수 갯수는 %d개\n", argc);
  if (argc == 3) {
    long a = strtol(argv[1], NULL, 10);
    long b = strtol(argv[2], NULL, 10);
    printf("%ld + %ld = %ld\n", a, b, a+b);
  }
  return 0;
}