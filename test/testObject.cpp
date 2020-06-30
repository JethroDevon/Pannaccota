#include "../lib/src/object.cpp"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


Object obj;
uint8_t* data = 0;

int main( int argc, const char* argv[] ){

  unsigned char myString [] = "This is my string";
  unsigned char otherString [] = "This also is my string";
  unsigned char anotherString [] = "This is yet another string";
  unsigned char finalString [] = "This is my final string";

  unsigned char label1 [] = "bits&bobs";
  unsigned char label2 [] = "nestedstuff";
  unsigned char label3 [] = "thisisatest";
  unsigned char label4 [] = "staticInts";
  
  uint8_t * my = &myString[0];
  uint8_t * other = &otherString[0];
  uint8_t * another = &anotherString[0];
  uint8_t * finale = &finalString[0];
  

  
  obj.push(my,&label1[0],1);
  obj.push(other,&label2[0],2);
  obj.push(another,&label3[0],3);
  obj.push(finale,&label4[0],4);
  
  obj.readAll();
  
}
		  
