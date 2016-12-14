#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

#ifndef TESTSERVER_H
#define TESTSERVER_H

#define PORT "5555"
#define MAXBUFFERSIZE 512
#define NETOPEN 1
#define NETREAD 2
#define NETWRITE 3
#define NETCLOSE 4

typedef struct MsgData {
  char ip_address[INET_ADDRSTRLEN];
  int sockfd;
  int msg_type;
} MsgData;

#endif
