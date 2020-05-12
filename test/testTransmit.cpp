#include "../lib/src/server.cpp"
#include "../lib/src/transmit.cpp"

#include <stdlib.h>
#include <string>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 

const char* message = "Moo Im A Cow";

int main( int argc, const char* argv[] ){
  
	Server srv(4445);	
	Transmit tra(srv.passConnection());
	tra.Send(message);
}
