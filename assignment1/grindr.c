#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(int argc, char **argv) {
  // Workload a
  void *arr[3000];
  for (size_t i = 0; i < 3000; i++) {
    arr[i]=malloc(1);
  }
  for (size_t i = 0; i < 3000; i++) {
    free(arr[i]);
  }
}
