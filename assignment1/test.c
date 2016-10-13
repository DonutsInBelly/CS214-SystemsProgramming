#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "mymalloc.h"

int main(int argc, char** argv) {
  struct obj1* test1 = mymalloc(sizeof(struct obj1));
  test1->a = 9;
  test1->b = 'l';
  printf("Number: %d\nCharacter: %c\n", test1->a, test1->b);

  struct obj2* test2 = mymalloc(sizeof(struct obj2));
  test2->b = 9.068;
  test2->c = 'p';
  test2->a = 8;
  printf("a= %d\nb= %ld\nc= %c\n", test2->a, test2->b, test2->c);
}
