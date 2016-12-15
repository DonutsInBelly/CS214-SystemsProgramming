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
#include "master.h"

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

  // wait for server to get ready to receive
  sleep(1);
  // Time to get serious: send the message type
  printf("netopen: Sending NETOPEN message...\n");
  int msgtype = htonl(NETOPEN);
  if (send(sockfd, &msgtype, sizeof(msgtype), 0) == -1) {
    perror("netopen send messagetype");
  }

  // wait for server to get ready to receive
  sleep(1);
  // Send pathname
  printf("netopen: Sending Path...\n");
  if (send(sockfd, pathname, strlen(pathname), 0) == -1) {
    perror("netopen send pathname");
  }

  // wait for server to get ready to receive
  sleep(1);
  // Send flags
  printf("netopen: Sending Flags...\n");
  int flagspayload = htonl(flags);
  if (send(sockfd, &flagspayload, sizeof(flagspayload), 0) == -1) {
    perror("netopen send flags");
  }

  // Setup to receive resultFD
  printf("netopen: Waiting to receive the result\n");
  int resultFD;
  int resultmsg;
  if ((resultmsg = recv(sockfd, &resultFD, sizeof(resultFD), 0)) == -1) {
    perror("netopen recv result");
    exit(1);
  }
  int result = ntohl(resultFD);
  printf("netopen: received result FD!\n");

  // check result and see if any errors
  int err;
  if (result == -1) {
    // if there was an error, receive the errno
    if ((resultmsg = recv(sockfd, &err, sizeof(err), 0)) == -1) {
      perror("netopen recv err");
    }
    errno = ntohl(err);
  }
  close(sockfd);

  return result;
}

ssize_t netread(int filedes, void *buf, size_t nbyte) {
  if (!initCalled) {
    fprintf(stderr, "netread: %s\n", "netread() called before netserverinit()");
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
  printf("netread: Connected to %s\n", ipstring);

  // wait for server to get ready to receive
  sleep(1);
  // Time to get serious: send the message type
  printf("netread: Sending NETREAD message...\n");
  int msgtype = htonl(NETREAD);
  if (send(sockfd, &msgtype, sizeof(int), 0) == -1) {
    perror("netread send messagetype");
  }

  // wait for server to get ready to receive
  sleep(1);
  // Send File Descriptor
  printf("netread: Sending File Descriptor...\n");
  int filedespayload = htonl(filedes);
  if (send(sockfd, &filedespayload, sizeof(int), 0) == -1) {
    perror("netread send filedespayload");
  }

  // wait for server to get ready to receive
  sleep(1);
  // Send size
  printf("netread: Sending nbyte...%d\n", nbyte);
  int sizepayload = htonl(nbyte);
  if (send(sockfd, &sizepayload, sizeof(int), 0) == -1) {
    perror("netread send sizepayload");
  }

  // Setup to receive result
  printf("netread: Waiting to receive the result\n");
  int resultsize;
  int resultmsg;
  if ((resultmsg = recv(sockfd, &resultsize, sizeof(resultsize), 0)) == -1) {
    perror("netread recv result");
  }
  int result = ntohl(resultsize);
  printf("netread: Received result size: %d!\n", result);

  // check result and see if any errors
  printf("netread: Checking for errors\n");
  if (result == -1) {
    int err;
    // if there was an error, receive the errno
    if ((resultmsg = recv(sockfd, &err, sizeof(err), 0)) == -1) {
      perror("netread recv err");
    }
  } else {
    printf("netread: No errors, sending resulting string\n");
    char resultstr[MAXBUFFERSIZE];
    if (recv(sockfd, resultstr, nbyte, 0) == -1) {
      perror("netread recv resultstr");
    }
    printf("%s\n", "hi");
  }
  close(sockfd);
  return result;
}

ssize_t netwrite(int filedes, const void *buf, size_t nbyte) {
  if (!initCalled) {
    fprintf(stderr, "netread: %s\n", "netread() called before netserverinit()");
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
  printf("netwrite: Connected to %s\n", ipstring);

  // wait for server to get ready to receive
  sleep(1);
  // Time to get serious: send the message type
  printf("netwrite: Sending NETWRITE message...\n");
  int msgtype = htonl(NETWRITE);
  if (send(sockfd, &msgtype, sizeof(int), 0) == -1) {
    perror("netwrite send messagetype");
  }

  // wait for server to get ready to receive
  sleep(1);
  // Send File Descriptor
  printf("netwrite: Sending File Descriptor...\n");
  int filedespayload = htonl(filedes);
  if (send(sockfd, &filedespayload, sizeof(int), 0) == -1) {
    perror("netwrite send filedespayload");
  }

  // wait for server to get ready to receive
  sleep(1);
  // Send size
  printf("netwrite: Sending nbyte...%d\n", nbyte);
  int sizepayload = htonl(nbyte);
  if (send(sockfd, &sizepayload, sizeof(int), 0) == -1) {
    perror("netwrite send sizepayload");
  }

  // wait for server to get ready to receive
  sleep(1);
  // Send string
  printf("netwrite: Sending string...\n");
  if (send(sockfd, buf, strlen(buf), 0) == -1) {
    perror("netwrite send buf");
  }

  // Setup to receive result
  printf("netwrite: Waiting to receive the result\n");
  int resultsize;
  int resultmsg;
  if ((resultmsg = recv(sockfd, &resultsize, sizeof(resultsize), 0)) == -1) {
    perror("netwrite recv result");
  }
  int result = ntohl(resultsize);
  printf("netwrite: Received result size: %d!\n", result);

  // check result and see if any errors
  printf("netwrite: Checking for errors\n");
  if (result == -1) {
    int err;
    // if there was an error, receive the errno
    if ((resultmsg = recv(sockfd, &err, sizeof(err), 0)) == -1) {
      perror("netwrite recv err");
    }
  }
  return result;
}

int netclose(int fd){
  if (!initCalled) {
    fprintf(stderr, "netopen: %s\n", "netclose() called before netserverinit()");
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
  printf("netclose: Connected to %s\n", ipstring);

  // wait for server to get ready to receive
  sleep(1);
  // Time to get serious: send the message type
  printf("netclose: Sending NETCLOSE message...\n");
  int msgtype = htonl(NETCLOSE);
  if (send(sockfd, &msgtype, sizeof(int), 0) == -1) {
    perror("netclose send messagetype");
  }

  // wait for server to get ready to receive
  sleep(1);
  // Send File Descriptor
  printf("netclose: Sending File Descriptor...\n");
  int filedespayload = htonl(fd);
  if (send(sockfd, &filedespayload, sizeof(int), 0) == -1) {
    perror("netclose send filedespayload");
  }
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
  char res[MAXBUFFERSIZE];
  char random[MAXBUFFERSIZE];
  int bsfd = open("/home/carlin/Documents/bs.txt", O_RDWR);
  int result = read(bsfd, random, 16);
  write(bsfd, "lol", 3);
  printf("%s\n", random);
  netserverinit("localhost", 0.5);
  int fd = netopen("/home/carlin/Documents/bs.txt", O_RDWR);
  netread(fd, res, 4);
  netwrite(fd, "lolol", 16);
  netclose(fd);
  return 0;
}
