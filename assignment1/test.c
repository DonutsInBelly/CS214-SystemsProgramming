#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "mymalloc.h"

int main(int argc, char** argv) {
  struct obj* test = malloc(sizeof(struct obj));
  test->a = 9;
  test->b = 'l';
  printf("Number: %d\nCharacter: %c\n", test->a, test->b);
}
