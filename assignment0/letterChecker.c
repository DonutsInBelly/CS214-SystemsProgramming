#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv) {
  if(isalpha(argv[1])) {
    printf("That's a letter\n");
  } else {
    printf("That's not a letter\n");
  }
}
