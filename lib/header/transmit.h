#ifndef TRANSMIT_H
#define TRANSMIT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

#define buffer_size 1024

//receives a connection from server and only transmits data
class Transmit{

  //data out, file descriptor, set up to listen
  int sockfd = 0;
  bool connected = false;
  
 public:

  Transmit(int);
  bool isConnected();
  void Send(const char*);
};
#endif
