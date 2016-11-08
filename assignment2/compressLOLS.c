#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  FILE *fp;
  // argv[1] is the name/path to the file
  if (access(argv[1], F_OK) == -1) {
    printf("%s\n", "File does not exist");
    return 1;
  }
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("%s\n", "File could not be opened.");
    return 1;
  }

  

  return 0;
}
