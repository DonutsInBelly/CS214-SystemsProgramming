#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "master.h"

void *msg_handler(void *vargp) {
  MsgData *first = (MsgData *)vargp;
  char buffer[MAXBUFFERSIZE];

  // NetOpen: 1
  // NetRead: 2
  // NetWrite: 3
  // NetClose: 4
  switch (first->msg_type) {
    case 1:
      printf("NetOpen: Request from %s\n", first->ip_address);
      // wait for pathname
      printf("NetOpen: Waiting for path message...\n");
      int pathmsg;
      if ((pathmsg = recv(first->clientfd, buffer, sizeof(NetOpen), 0)) == -1) {
        perror("netopen path");
        exit(1);
      }
      buffer[pathmsg] = '\0';
      printf("NetOpen: Received path: %s\n", buffer);

      printf("NetOpen: Waiting for flags message...\n");
      int flagsrecv;
      int flagsmsg;
      if ((flagsmsg = recv(first->clientfd, &flagsrecv, sizeof(int), 0)) == -1) {
        perror("netopen flags");
      }
      int flags = ntohl(flagsmsg);
      printf("NetOpen: Received flags: %x\n", flags);

      // try actually open()ing the file and then sending the result FD back
      printf("NetOpen: Trying to open the file\n");
      int result = open(buffer, flags);
      int resultpayload = htonl(result);
      printf("NetOpen: Sending netopen result: %x\n", resultpayload);
      if (send(first->clientfd, &resultpayload, sizeof(int), 0) == -1) {
        perror("netopen send result");
      }
      // if there was an error getting the resulting FD
      if (result == -1) {
        // send serrno across the wire
        printf("NetOpen: Sending errno :%x\n", errno);
        int errnopayload = htonl(errno);
        if (send(first->clientfd, &errnopayload, sizeof(int), 0) == -1) {
          perror("netopen send errno");
        }
      }
      printf("NetOpen: Finished Operation.\n");
      close(first->clientfd);
      break;
    case 2:
      printf("NetRead requested from %s\n", first->ip_address);
      break;
    case 3:
      printf("NetWrite requested from %s\n", first->ip_address);
      break;
    case 4:
      printf("NetClose requested from %s\n", first->ip_address);
      break;
  }
}

int main(int argc, char const *argv[]) {
  int sockfd;
  int recfd;
  struct addrinfo hints;
  struct addrinfo *res;

  printf("Spinning up netfileserver!\n");

  // set up hints for getaddrinfo
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, PORT, &hints, &res);

  // set up the socket descriptor
  printf("Setting up socket descriptor...\n");
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  // binds the socket descriptor to the ip
  printf("Binding socket descriptor to IP Address Info...\n");
  bind(sockfd, res->ai_addr, res->ai_addrlen);

  // sets the socket descriptor to listen for connections
  listen(sockfd, 10);

  char currentAddr[INET_ADDRSTRLEN];
  struct sockaddr_storage clientAddr;
  socklen_t addr_size;
  while (1) {
    // accept() waits for connections to come in to connect to
    printf("Waiting to accept new connections...\n");
    addr_size = sizeof clientAddr;
    recfd = accept(sockfd, (struct sockaddr *)&clientAddr, &addr_size);
    if (recfd == -1) {
      perror("accept");
    }

    // inet_ntop puts the client's ip into a string to work with
    inet_ntop(clientAddr.ss_family, (void *)((struct sockaddr *)res->ai_addr), currentAddr, sizeof currentAddr);
    printf("Client connected: %s\n", currentAddr);

    // Set up message to pass to msg_handler()
    MsgData *data = malloc(sizeof(MsgData));
    strcpy(data->ip_address, currentAddr);
    data->clientfd = recfd;

    // Receiving the first message from the client
    int msg_type;
    int msg;
    if ((msg = recv(recfd, &msg_type, sizeof(int), 0)) == -1) {
      perror("main recv");
      exit(1);
    }
    data->msg_type = ntohl(msg_type);
    printf("Received: %x from %s\n", data->msg_type, currentAddr);

    // Threading stuff. Should create a worker thread to pass data to msg_handler.
    pthread_t child;
    pthread_create(&child, NULL, msg_handler, (void *)data);
    pthread_detach(child);
  }
  return 0;
}
