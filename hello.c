// 11-1 
#include <stdio.h>

void is_prime(int *arr);
int main() {
  int prime_list[1000];

  for (int i = 0; i < 1000; i++) {
    prime_list[i] = 1;
  }

  prime_list[0] = 0;
  prime_list[1] = 0;


  is_prime(prime_list);

  for (int i = 2; i < 1000; i++) {
    if (prime_list[i] == 1) {
      printf("%d\n", i);
    }
  }

  return 0;
}

void is_prime(int *arr) {
  for (int i = 2; i * i < 1000; i++) {
    if (arr[i] == 1) {
      for (int j = i * i; j < 1000; j += i) {
        arr[j] = 0;
      }
    }
  }
}

