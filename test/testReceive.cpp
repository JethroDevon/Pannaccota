#include "../lib/src/receive.cpp"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>



int main( int argc, const char* argv[] ){
  
	printf( "testing receive class, please send connection to:\n" );
	printf( "IP:%s and Port:%i\n", argv[1], atoi(argv[2]));
	Receive rec( std::string(argv[1]), atoi(argv[2]));	
	rec.Connect();
	while(!rec.Read());

	std::cout << rec.getAsString() << std::endl;
	std::cout << std::hex << rec.getAsBytes() << std::endl;
	rec.Close();
}


