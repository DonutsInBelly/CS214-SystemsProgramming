#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

#ifndef MASTER_H
#define MASTER_H

#define PORT "5555"
#define MAXBUFFERSIZE 512
#define INVALID_FILE_MODE -214
#define NETOPEN 1
#define NETREAD 2
#define NETWRITE 3
#define NETCLOSE 4

typedef struct MsgData {
  char ip_address[INET_ADDRSTRLEN];
  int clientfd;
  int msg_type;
} MsgData;

typedef struct NetOpen {
  char path[MAXBUFFERSIZE-1];
  int flags;
} NetOpen;

#endif
