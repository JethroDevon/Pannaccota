#include "../lib/src/object.cpp"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


Object obj;

int main( int argc, const char* argv[] ){

  unsigned char myString [] = "This is my string";
  unsigned char otherString [] = "This also is my string";
  unsigned char anotherString [] = "This is yet another string";
  unsigned char finalString [] = "This is my final string";
 
  unsigned char* my = &myString[0];
  unsigned char* other = &otherString[0];
  unsigned char* another = &anotherString[0];
  unsigned char* finale = &finalString[0];
  

  obj.push(my,"random",1);
  obj.push(other,"folder",2);
  obj.push(another,"string",3);
  obj.push(finale,"uint8",4);
  obj.getAll(obj.head);
  
}
		  
