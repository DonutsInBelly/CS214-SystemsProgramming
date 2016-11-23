#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "lols.h"

void *RLE(void *vargp) {
  Data *d = vargp;
  printf("%s\n", d->str);
  printf("Number of Parts: %d\n", d->parts);
  printf("toStart: ");
  for (size_t i = 0; i < d->parts; i++) {
    printf("%d, ", d->toStart[i]);
  }
  return;
}

int main(int argc, char const *argv[]) {
  FILE *fp;
  FILE *count;

  // argv[2] is the number of parts
  // Ensures we get a number of parts
  if (argc != 3) {
    printf("%s\n", "Error: Incorrect amount of arguments. Please use:\n\"./asst2 [text file to be compressed] [Number of parts]\"");
    return 1;
  }
  int numberOfParts = atoi(argv[2]);
  printf("%ld\n", numberOfParts);

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

  // Now that we know how big it is, we can just get the entire string
  pthread_t tid;
  printf("%s\n", "Malloc");
  Data *d = malloc(sizeof(struct Data));
  d->str = malloc(inputLength);
  char *toCompress = malloc(sizeof(char)*inputLength);
  FILE *fp2 = fopen(argv[1], "r");
  printf("%s\n", "Get Line from file");
  fgets(toCompress, inputLength, fp2);

  printf("%s\n", "add number of parts");
  d->parts = numberOfParts;
  printf("%ld\n", numberOfParts);
  printf("%s\n", "doesn't like str");
  d->str = toCompress;
  int i;
  int segLength = inputLength/numberOfParts;
  for (i = 0; i < numberOfParts; i++) {
    printf("%s\n", "unhappy with counting");
    d->toStart[i] = i*segLength;
  }

  printf("%s\n", "Creating thread");
  pthread_create(&tid, NULL, RLE, (void *)d);
  pthread_exit(NULL);
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
