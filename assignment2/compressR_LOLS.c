#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "lols.h"
#include "compressR_worker_LOLS.h"
#include "utils.h"
//include everything just in case

void compressR_LOLS(char* file, int parts) {
  //**--- Routine file checking
  FILE *fp;
  FILE *count;
  // file is the name/path to the file
  // Ensures the file is valid
  if (access(file, F_OK) == -1) {
    printf("%s\n", "File does not exist");
    return 1;
  }
  fp = fopen(file, "r");

  // ensures that file streams can open the given file
  if (fp == NULL) {
    printf("%s\n", "File could not be opened.");
    return 1;
  }

  // check if parts greater than resources available.
  count = fopen(file, "r");
  fseek(count, 0L, SEEK_END);
  int totalSize = ftell(count);
  if(totalSize<parts) {
    fclose(count);
    printf("%s\n", "Amount of parts requested is larger than the actual size of the file to be compressed.");
    return 1;
  }
  fclose(count);
  //**--- End routine file checking
  printf("%s\n", "Finished routine checks");

  pthread_t *threads = malloc(sizeof(pthread_t)*parts);

  FileData *data = (FileData *)malloc(sizeof(FileData));
  data->name = getFileName(file);
  data->path = getOutputFile(file);
  data->fullpath = file;
  data->partition = computePartitionSize(file, parts, 0);

  /*parallel processing starts here*/
  /*not sure how connect lols.c soooo
  *i'm gonna assume i have a lot of vars that i don't
  *like inputLength and numberOfParts*/

  int partition;
  partition = computePartitionSize(file, parts, 0);
  int startIndex = 0;

  int i;
  for (i = 0; i < parts-1; i++) {
    if(partition>totalSize) {
      partition = totalSize;
    }
    FileData *info = (FileData *)malloc(sizeof(FileData));
    info->name = getFileName(file);
    info->path = getOutputFile(file);
    info->fullpath = file;
    info->startIndex = startIndex;
    info->partitionNumber = i;
    info->partition = partition;
    int pid = fork();
    if(pid == -1) {
      printf("%s\n", "Fork Failed!!");
      return;
    } else if(pid == 0) {
      worker(info);
      exit(0);
    }
  }
  if(parts == 1) {
    // UHHHHHHH
  }
  wait(NULL);
}

int main(int argc, char const *argv[]) {
  FILE *fp;
  FILE *count;

  // argv[2] is the number of parts
  // Ensures we get a number of parts
  if (argc != 3) {
    printf("%s\n", "Error: Incorrect amount of arguments. Please use:\n\"./asst2 [text file to be compressed] [Number of parts]\"");
    return 1;
  }
  int numberOfParts = atoi(argv[2]);
  printf("%ld\n", numberOfParts);

  // argv[1] is the name/path to the file
  // Ensures the file is valid
  if (access(argv[1], F_OK) == -1) {
    printf("%s\n", "File does not exist");
    return 1;
  }
  fp = fopen(argv[1], "r");
  count = fopen(argv[1], "r");

  // ensures that both file streams can open the given file
  if (fp == NULL || count == NULL) {
    printf("%s\n", "File could not be opened.");
    return 1;
  }

  fclose(fp);
  fclose(count);

  // Compression starts here
  compressR_LOLS(argv[1], numberOfParts);
}




//
// pid_t * children = (pid_t *) malloc(sizeof(pid_t)*parts);
//
// //parent process waiting on all children
// pid_t p;
// int status;
// int j = 0;
// //need to check that children is populated
// while(j < arts) {
//   p = waitpid(children[j], &status, WNOHANG);
//   j++;
// }
//
//
// //dis where forking starts
// pid_t pid;
//
// int i = 0;
// while (i < parts) {
//   pid = fork();
//
//   if (pid > 0) {
//     children[i] = pid;
//     i++;
//     //sleep(1); ?
//   } else if (pid < 0){
//     //error handling do later
//     printf("Fork has failed.\n");
//     //perror("Fork has failed");
//     exit(1);
//   } else {
//     //child process, compress here
//
//     write();
//   }
//
//
//
// }
//
// free(children);
