#include "../lib/src/server.cpp"

#include <stdlib.h>
#include <string>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 

const char *hello = "wuff! wuff!";
char buffer[1024] = {0};

int main( int argc, const char* argv[] ){
  
	printf( "testing Server functionality, connect to listening port%i\n", argv[1] );
              
	Server srv(atoi(argv[1]));	
	int fd = srv.passConnection();
	send(fd , hello , strlen(hello) , 0 ); 
}
