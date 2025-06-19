// 15-2 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_text_file(const char *filename, const char *change_text, const char *new_text);

int main(int argc, char **argv) {
  replace_text_file("test.txt", "hi", "ha");
  return 0;
}

void replace_text_file(const char *filename, const char *change_text, const char *new_text) {
  FILE *fp = fopen(filename, "r+");

  if (fp == NULL) {
    printf("error");
    return;
  }

  char word[100];
  while (fscanf(fp, "%s", word) != EOF) {
    if (strcmp(word, change_text) == 0) {
      fseek(fp, -(strlen(word)+1), SEEK_CUR);
      fputs(new_text, fp);
      fflush(fp);
    }
  }
}

