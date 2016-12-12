#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// The port to connect to
#define PORT "5555"
// How many connections are allowed
#define QUEUELIMIT 10

int netserverinit(char * hostname) {
  int sockfd;
  struct addrinfo hints;
  struct addrinfo *res;
  int status;

  // set up hints for getaddrinfo() to return ip information
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET; // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP Stream Sockets
  hints.ai_flags = AI_PASSIVE;

  printf("%s\n", "Getting Address Info");
  if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return 2;
  }

  // Tutorial code
  struct addrinfo *p;
  char ipstr[INET6_ADDRSTRLEN];
  printf("IP addresses for %s:\n\n", hostname);

  for(p = res;p != NULL; p = p->ai_next) {
    void *addr;
    char *ipver;

    // get the pointer to the address itself,
    // different fields in IPv4 and IPv6:
    if (p->ai_family == AF_INET) { // IPv4
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } else { // IPv6
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    }

    // convert the IP to a string and print it:
    inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
    printf("  %s: %s\n", ipver, ipstr);
  }

  freeaddrinfo(res); // free the linked list

  return 0;
}

int main(int argc, char const *argv[]) {
  // TODO: add argument checking
  if (argc != 2) {
    printf("%s\n", "Error: Not enough arguments given. Please run with:\n./server [hostname]");
    exit(1);
  }
  // initializes the server
  printf("%s\n", argv[1]);
  netserverinit(argv[1]);
  return 0;
}
