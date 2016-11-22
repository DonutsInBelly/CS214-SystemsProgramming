#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "lols.h"

// test/text1.txt turns into text1.txt
char *getFileName(char *file) {
  if(strstr(file, "/") != NULL) {
    char *tmp = (char *)malloc(sizeof(char *));
    strcpy(tmp, file);
    char *dir;
    int l = 0;
    dir = strstr(tmp, "/");
    do{
      printf("%s\n", "loop");
      l = strlen(dir) + 1;
      tmp = &tmp[strlen(tmp)-l+2];
      dir = strstr(tmp, "/");
    }while(dir);
    return tmp;
  }
  return file;
}

// test/text1.txt turns into test/text1_LOLS
char *getOutputFile(char *file) {
  char *output = (char *)malloc(strlen(file)+strlen("_LOLS")+2);
  sprintf(output, "%s_LOLS", file);
  int i;
  for (i = 0; i < strlen(output); i++) {
    if(output[i] == '.') {
      output[i] = '_';
    }
  }
  return output;
}

// if first partition, then add totalsize%howMany and return
int computePartitionSize(char *file, int howMany, int firstFlag) {
  if (access(argv[1], F_OK) == -1) {
    printf("%s\n", "File does not exist");
    return -1;
  }

  FILE *fp = fopen(file, "r");

  fseek(fp, 0, SEEK_END);
  int totalSize = ftell(fp);
  if(firstFlag) {
    return ((totalSize/howMany)+(totalSize%howMany));
  }
  return totalSize/howMany;
}
