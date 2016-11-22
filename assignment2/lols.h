#ifndef STD
#define STD

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#endif


#ifndef LOLS_H
#define  LOLS_H

typedef struct Segment{
  char symbol;
  int occurences;
} Segment;

typedef struct FileData{
  char* name;
  char* path;
  char* fullpath;
  int partition;
  int partitionNumber;
} FileData;

char * getFileName(char *file);
char * getOutputFile(char *file);
#endif
