#include <stdio.h>
#include <stdlib.h>

int main() {
  char mychar[10];
  int * intlocation = 3632; // stores 3632
  mychar[5] = intlocation;
  printf("%d\n", *(&mychar[5]));
}
