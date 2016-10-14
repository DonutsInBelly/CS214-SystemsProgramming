#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "mymalloc.h"

int main(int argc, char** argv) {
  struct obj1* test1 = mymalloc(sizeof(struct obj1));
  test1->a = 90;
  test1->b = 't';
  printf("Address of test1: 0x%02X\n", test1);
  printf("Number: %d\nCharacter: %c\n", test1->a, test1->b);
  //printf("Field a is at: 0x%02X\nField b is at: 0x%02X\n", );

  struct obj2* test2 = mymalloc(sizeof(struct obj2));
  test2->a = 8;
  test2->b = 9.068;
  test2->c = 'p';
  printf("Address of test2: 0x%02X\n", test2);
  printf("a= %d\nb= %lf\nc= %c\n", test2->a, test2->b, test2->c);
}
