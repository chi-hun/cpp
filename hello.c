// 15-2 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fuc.h"

struct BALL {
  int x;
  int y;
};

int main(int argc, char **argv) {

  int n;
  scanf("%d", &n);

  struct BALL *balls = (struct BALL *)malloc(sizeof(struct BALL) * n);

  int d_x = 0;
  int d_y = 0;

  for (int i = 0; i < n; i++) {
    balls[i].x = d_x;
    balls[i].y = d_y;
    d_x++;
    d_y++;
  }

  for (int i = 0; i < n; i++) {
    printf("%d %d\n", balls[i].x, balls[i].y);
  }

  free(balls);

  return 0;
}