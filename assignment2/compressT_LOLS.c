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

void compressT_LOLS(char* file, int parts) {
  //**--- Routine file checking
  FILE *fp;
  FILE *count;
  // file is the name/path to the file
  // Ensures the file is valid
  if (access(file, F_OK) == -1) {
    printf("%s\n", "File does not exist");
    return 1;
  }
  fp = fopen(file, "r");

  // ensures that file streams can open the given file
  if (fp == NULL) {
    printf("%s\n", "File could not be opened.");
    return 1;
  }

  // check if parts greater than resources available.
  count = fopen(file, "r");
  fseek(count, 0L, SEEK_END);
  if(ftell(count)<parts) {
    fclose(count);
    printf("%s\n", "Amount of parts requested is larger than the actual size of the file to be compressed.");
    return 1;
  }
  fclose(count);
  //**--- End routine file checking
  printf("%s\n", "Finished routine checks");

  pthread_t *threads = malloc(sizeof(pthread_t)*parts);

  FileData *data = (FileData *)malloc(sizeof(FileData));
  data->name = getFileName(file);
  data->path = getOutputFile(file);
  data->fullpath = file;
  data->partition = computePartitionSize(file, parts, 0);

  int threadCount;
  int totalBytesRead = 0;
  for (threadCount = 0; threadCount < parts; threadCount++) {
    FileData *threadData = (FileData *)malloc(sizeof(FileData));
    threadData->name = getFileName(file);
    threadData->path = getOutputFile(file);
    sprintf(threadData->path, "%s%d", threadData->path, threadCount+1);
    printf("%s\n", threadData->path);
    threadData->fullpath = file;
    threadData->partitionNumber = threadCount;
    if(threadCount == 0) {
      threadData->partition = computePartitionSize(file, parts, 1);
    } else {
      threadData->partition = computePartitionSize(file, parts, 0);
    }
    threadData->startIndex = totalBytesRead;
    printf("Start: %d\n", threadData->startIndex);
    totalBytesRead += threadData->partition;
    pthread_create(&threads[threadCount], NULL, compress, (void *)threadData);
  }
  int j;
  for (j = 0; j < parts; j++) {
    pthread_join(threads[j], NULL);
  }
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

  fclose(fp);
  fclose(count);

  // Compression starts here
  compressT_LOLS(argv[1], numberOfParts);
}
