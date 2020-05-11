#ifndef RECEIVE_H
#define RECEIVE_H

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
#include <cstring>
#include <iostream>
#include <memory.h>

#define stack_num 6
#define buffer_size 1024

//listens for a connections and stores incoming data in a buffer
class Receive{

  int listenfd = 0, message_pos = 0, selected_stack = 0, PORT = 0;
  struct sockaddr_in serv_addr;
  time_t ticks;
  std::string IP = "";
  bool connected = false;
  
  //six stacks is good number for this stage 
  unsigned char rec_stack[stack_num][buffer_size];
  public:

    Receive(std::string _IP, int _PORT);  
    bool Connect();
    bool Read();
    std::string getBuffer(); ///make thread safe later
    void selectBuffer(int);
    std::string getAsString();
    unsigned char *getAsBytes();
    void Close();
    Receive(const Receive &r);
    ~Receive();
};
#endif
