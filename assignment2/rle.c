#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char ** argv) {

  FILE *fp;
  fp = fopen(argv[1], r)
  char * line = malloc(sizeof(char)*50);
  while (1) {

    line = fgets(fp);
    if (feof(fp)) {
      break;
    }

    char * c = calloc(1, sizeof(char)*2);
    char * d = calloc(1, sizeof(char)*2);
    char * e = calloc(1, sizeof(char)*50);
    char * num = calloc(1, sizeof(char)*3);
    int count = 0;
    int i = 1;
    c = strcpy(c, line[0]);
    d = strcpy(d, line[1]);

    while(line[i]!=NULL) {
      while (strcmp(c, d)==0) {
        count++;
        d = line[i];
        i++;
      }

      e = strcat(e, c);
      e = strcat(e, itoa(count, num, 10));

      c = str[i];
      d = str[i++];
    }

    printf("%s\n", e);


  }
  fclose(fp);

  return 0;
}
