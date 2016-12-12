#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define PORT 5555
#define INVALID_FILE_MODE -214

// Global Variables
int connectionMode;
struct addrinfo *hostaddrinfo;

// verifies that the host exists.
// 'netserverinit' should return -1 on failure and 0 on success.
int netserverinit(char *hostname, int filemode) {
  int sockfd =-1;
  struct addrinfo hints;
  int status;

  // set up hints for getaddrinfo() to return ip information
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET; // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP Stream Sockets
  hints.ai_flags = AI_PASSIVE;

  // Checks that the hostname exists.
  // if not, it returns -1 and sets h_errno to HOST_NOT_FOUND
  printf("Getting Address Info for: %s with filemode: %x\n", hostname, filemode);
  if ((status = getaddrinfo(hostname, NULL, &hints, &hostaddrinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    h_errno = HOST_NOT_FOUND;
    return -1;
  }

  // Check and Set file mode
  // If its not 0, 1, or 2 it returns -1 and sets h_errno to INVALID_FILE_MODE
  if (filemode < 0 || filemode > 2) {
    fprintf(stderr, "filemode: %s\n", "Invalid File Mode");
    h_errno = INVALID_FILE_MODE;
    return -1;
  }
  connectionMode = filemode;

  printf("%s\n", "Success! Hostname found!");
  return 0;
}

// Debugging
int main(int argc, char const *argv[]) {
  netserverinit("localhost", 0.5);
  return 0;
}
