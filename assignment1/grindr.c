#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(int argc, char **argv) {
  // Workload a
  void *arr[3000];
  for (size_t i = 0; i < 20; i++) {
    arr[i]=malloc(1);
    //arr[i]='a';
    printf("Allocating %d at address: 0x%02X\n", i, &arr[i]);
  }
  for (size_t i = 0; i < 3000; i++) {
    free(arr[i]);
    printf("Freeing %d\n", i);
  }
}
