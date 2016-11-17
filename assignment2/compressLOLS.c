#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "lols.h"

int main(int argc, char const *argv[]) {
  FILE *fp;
  FILE *count;
  // argv[1] is the name/path to the file
  // Ensures the file is valid
  if (access(argv[1], F_OK) == -1) {
    printf("%s\n", "File does not exist");
    return 1;
  }
  fp = fopen(argv[1], "r");
  count = fopen(argv[1], "r");

  // ensures that both file streams can open the given file
  if (fp == NULL || count == NULL) {
    printf("%s\n", "File could not be opened.");
    return 1;
  }

  // Count how big the input is
  int inputLength;
  while (fgetc(count) != EOF) {
    inputLength++;
  }
  fclose(count);
  printf("%ld\n", inputLength);

  // Compress!
  int index = 0;
  Segment seg[inputLength];
  char curr = fgetc(fp);
  seg[index].symbol = curr;
  seg[index].occurences = 0;
  do {
    if (curr != seg[index].symbol && isalpha(curr)) {
      printf("%c\n", curr);
      index++;
      seg[index].symbol = curr;
      seg[index].occurences = 1;
    } else if (curr == seg[index].symbol && isalpha(curr)){
      seg[index].occurences += 1;
    }
    curr = fgetc(fp);
  } while (curr != EOF);

  for (size_t i = 0; i <= index; i++) {
    printf("%d%c", seg[i].occurences, seg[i].symbol);
  }
  printf("\n");
  return 0;
}
