#include "../header/transmit.h"

Transmit::Transmit(int _fd):sockfd(_fd){

  connected = true;
};

bool Transmit::isConnected(){

  return connected;
}

void Transmit::Send(const char* data_out){

  send(sockfd , data_out , strlen(data_out) , 0 ); 
}
