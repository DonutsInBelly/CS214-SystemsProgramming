#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include "lols.h"

void compressT_LOLS(char* file, int parts) {
  //**--- Routine file checking
  FILE *fp;
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
  //**--- End routine file checking
  printf("%s\n", "Finished routine checks");

  FileData *data = (FileData *)malloc(sizeof(FileData));
  printf("%s\n", "apparently thats legal");
  data->name = getFileName(file);
  data->path = getOutputFile(file);
  data->fullpath = file;

  pthread_t threads[parts];

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
  compressT_LOLS(argv[1], argv[2]);
}
