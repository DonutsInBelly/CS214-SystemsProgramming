#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "mymalloc.h"

int main(int argc, char** argv) {
  struct obj1* test1 = malloc(sizeof(struct obj1));
  test1->a = 90;
  test1->b = 't';
  printf("Address of test1: 0x%02X\n", test1);
  printf("Number: %d\nCharacter: %c\n", test1->a, test1->b);
  //printf("Field a is at: 0x%02X\nField b is at: 0x%02X\n", );

  struct obj3* test3 = malloc(sizeof(struct obj3));

  struct obj2* test2 = malloc(sizeof(struct obj2));
  test2->a = 8;
  test2->b = 9.068;
  test2->c = 'p';
  printf("Address of test2: 0x%02X\n", test2);
  printf("a= %d\nb= %lf\nc= %c\n", test2->a, test2->b, test2->c);
  free(test2);
  free(test2+100);

  printf("%s\n", "int pointer");
  int *x;
  free(x);

  printf("%s\n", "primitive data type");
  int l;
  free(l);

  struct obj1* test3 = malloc(sizeof(struct obj1));
  test3->a = 1063;
  test3->b = 'f';
  printf("Address of test3: 0x%02X\n", test3);
  printf("Number: %d\nCharacter: %c\n", test3->a, test3->b);
}
