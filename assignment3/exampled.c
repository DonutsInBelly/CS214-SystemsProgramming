#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int netserverinit(char * hostname) {
  int listenFD = 0;
  int connectionFD = 0;

  struct sockaddr_in serverAddr;

  char sendBuffer[1025];
  time_t ticks;

  listenFD = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serverAddr, '0', sizeof(serverAddr));
  memset(sendBuffer, '0', sizeof(sendBuffer));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(5000);

  bind(listenFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

  listen(listenFD, 10);

  while (1) {
    connectionFD = accept(listenFD, (struct sockaddr*)NULL, NULL);

    ticks = time(NULL);

    snprintf(sendBuffer, sizeof(sendBuffer), "%.24s\r\n", ctime(&ticks));

    write(connectionFD, sendBuffer, strlen(sendBuffer));

    close(connectionFD);
    sleep(1);
  }
}

int main(int argc, char const *argv[]) {
  // TODO :adjust for extension A
  if(argc != 1) {
    printf("%s\n", "Not enough arguments!!\nPlease run: \"./server [hostname] [filemode]\"");
  }
  netserverinit(argv[1]);
  //netserverinit(argv[1], argv[2]);
  return 0;
}
