#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "libnetfiles.h"

// Global Variables
int initCalled = 0; // boolean to check if netserverinit() was called successfully
int connectionMode;
struct addrinfo hints;
struct addrinfo *serveraddrinfo;

// opens a file on the server through a socket and returns its file descriptor
int netopen(const char *pathname, int flags) {
  if (!initCalled) {
    fprintf(stderr, "netopen: %s\n", "netopen() called before netserverinit()");
    exit(-1);
  }

  // Get socket descriptor and connect to it
  int sockfd = -1;
  sockfd = socket(serveraddrinfo->ai_family, serveraddrinfo->ai_socktype, serveraddrinfo->ai_protocol);
  int connectionStatus = connect(sockfd, serveraddrinfo->ai_addr, serveraddrinfo->ai_addrlen);
  if (connectionStatus != 0) {
    perror("connect");
    return -1;
  }

  // Print that we've connected to the IP Address
  char ipstring[INET_ADDRSTRLEN];
  inet_ntop(serveraddrinfo->ai_family, (void *)((struct sockaddr *)serveraddrinfo->ai_addr), ipstring, sizeof ipstring);
  printf("netopen: Connected to %s\n", ipstring);

  // Time to get serious: send the message type
  int msgtype = htonl(NETOPEN);
  if (send(sockfd, &msgtype, sizeof(int), 0) == -1) {
    perror("netopen send messagetype");
  }

  // Setup to receive data
  char buffer[MAXBUFFERSIZE];
  int msg;
  if ((msg = recv(sockfd, buffer, MAXBUFFERSIZE-1, 0)) == -1) {
    perror("netopen recv");
    exit(1);
  }
  buffer[msg] = '\0';
  printf("Received: %s\n", buffer);
  close(sockfd);

  return 0;
}

// verifies that the host exists.
// 'netserverinit' should return -1 on failure and 0 on success.
int netserverinit(char *hostname, int filemode) {
  int sockfd =-1;
  int status;

  // set up hints for getaddrinfo() to return ip information
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET; // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP Stream Sockets
  hints.ai_flags = AI_PASSIVE;

  // Checks that the hostname exists.
  // if not, it returns -1 and sets h_errno to HOST_NOT_FOUND
  printf("Getting Address Info for: %s with filemode: %x\n", hostname, filemode);
  if ((status = getaddrinfo(hostname, PORT, &hints, &serveraddrinfo)) != 0) {
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
  initCalled = 1;
  return 0;
}

// Debugging
int main(int argc, char const *argv[]) {
  netserverinit("localhost", 0.5);
  netopen("/home/carlin/Documents/bs.txt", O_RDWR);
  return 0;
}
