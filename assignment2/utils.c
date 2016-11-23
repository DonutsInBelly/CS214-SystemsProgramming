#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include "lols.h"

void *compress(void *vargp) {
  FileData *data = (FileData *)vargp;
  char * tmp = data->fullpath;
  FILE *fp = fopen(tmp, "r");

  FILE *out = fopen(data->path, "a");
  /*
  if (access(data->path, F_OK) != -1 ) {
    fclose(fp);
    fclose(out);
    return NULL;
  }*/

  fseek(fp, 0L, SEEK_END);
  int size = ftell(fp);
  rewind(fp);
  printf("%d\n", size);

  int index = data->startIndex;
  int segIndex = 0;
  Segment seg[size];
  fseek(fp, data->startIndex, SEEK_SET);
  char curr = fgetc(fp);
  printf("%s\n", "Hello");

  seg[segIndex].symbol = curr;
  seg[segIndex].occurences = 0;
  printf("%s\n", "starting looop");
  do {
    printf("Starting Position: %s \nCurrentIndex: %d with %c\n", data->path,index, curr);
    if(curr != seg[segIndex].symbol && isalpha(curr)) {
      index++; segIndex++;
      printf("Adding %c to Segments\n", curr);
      seg[segIndex].symbol = curr;
      seg[segIndex].occurences = 1;
    } else if(curr == seg[segIndex].symbol && isalpha(curr)) {
      seg[segIndex].occurences += 1;
    }
    curr = fgetc(fp); index++;
  } while(index < (data->startIndex + data->partition+1));
  int k;
  for (k = segIndex; k >= 0; k--) {
    writeToFile(data->path, seg[k]);
  }
  printf("%s\n", "done");
  fclose(fp);
  fclose(out);
}

void writeToFile(char *path, Segment seg) {
  FILE *out = fopen(path, "a");
  if (seg.occurences == 1) {
    printf("Appending : %c\n", seg.symbol);
    fprintf(out, "%c", seg.symbol);
  } else if (seg.occurences == 2) {
    printf("Appending : %c\n", seg.symbol);
    fprintf(out, "%c%c", seg.symbol, seg.symbol);
  } else {
    printf("Appending : %c\n", seg.symbol);
    fprintf(out, "%d%c", seg.occurences, seg.symbol);
  }
}
