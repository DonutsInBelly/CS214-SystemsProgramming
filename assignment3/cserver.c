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
#include <pthread.h>

#define PORT "5555"

void *threading (void *param)

struct fds {
  /*needs int of fd
  file name
  access mode
  i think that's it for now?
  */

}

//method declaration. actual body of method under main
void *threading (void *param)


int main(int argc, char const *argv[]) {
  int sockfd;
  int newfd;
  struct addrinfo hints;
  struct addrinfo *res;

  // set up hints for getaddrinfo
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, PORT, &hints, &res);

  // set up the socket descriptor
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  bind(sockfd, res->ai_addr, res->ai_addrlen);

  listen(sockfd, 10);

  char currentAddr[INET_ADDRSTRLEN];
  struct sockaddr_storage clientAddr;
  socklen_t addr_size;
  while (1) {
    addr_size = sizeof clientAddr;
    newfd = accept(sockfd, (struct sockaddr *)&clientAddr, &addr_size);
    if (newfd == -1) {
      perror("accept:")
    }

    /* builds an ip address into a string for printing
    inet_ntop(clientAddr.ss_family, (void *)((struct sockaddr *)clientAddr), currentAddr, sizeof currentAddr);
    printf("Client connected: %s\n", currentAddr);
    */
    //printf("Client connected\n");

    //threading starts here?????
    pthread_t *thread = malloc(sizeof(pthread_t));

    pthread_create(&thread, NULL, threading, NULL);


  }

void *threading (void *param /*possibly not void oop*/) { //also probably does not return null
  int newfd;

  pthread_detach(pthread_self());

  //do these all need to be separate functions?

  /*asdfjkl;
  netserverinit
  h e l p
  */


  /*netopen
  just give it a file descriptor! worry about errors later????
  how check for permission / errors
  record it in file descriptor...struct
  can i use open here?
  or send/receive?
  */


  /*netread
  does it have to be open??? yes. okay good
  fd -> filename
  permissions???
  if buf > nbyte error
  */

  /*netwrite
  like netread
  fd -> filename
  permissions
  if buf > nbyte error
  */

  /*netclose
  just delete fd???
  free all mem and stuff
  how does this fail?!?!?!??!
  */

  return NULL;
  }



  return 0;
}