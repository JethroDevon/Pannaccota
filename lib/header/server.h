#ifndef Server_H
#define Server_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <iostream>
#include <memory.h>

//listens for a connections and stores incoming data in a buffer
class Server{

  int servfd = 0, PORT = 0, opt = 1, addr_len = 0;
  std::string IP = "";
  struct sockaddr_in serv_addr;

  public:
  
    Server(int _PORT);
    int passConnection();

};
#endif
