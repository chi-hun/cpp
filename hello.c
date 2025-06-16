// 15-2 
#include <stdio.h>
#include <string.h>

struct Human {
  char name[20];
  int age;
  int height;
  int weight;
};

int input_human(struct Human *h, const char *name, int age, int height, int weight);

int main() {
  struct Human man_1;
  struct Human *man_1_p = &man_1;
  input_human(man_1_p, "kim", 40, 175, 80);
  printf("%s %d %d %d\n", man_1.name, man_1.age, man_1.height, man_1.weight);

  return 0;
}

int input_human(struct Human *h, const char *name, int age, int height, int weight) {
  strcpy(h->name, name);
  h->age = age;
  h->height = height;
  h->weight = weight;
  return 0;
}