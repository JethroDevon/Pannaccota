#include "../lib/src/object.cpp"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


Object obj, obj2, obj3, obj4, obj5;
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
  
  uint8_t* my = &myString[0];
  uint8_t* other = &otherString[0];
  uint8_t* another = &anotherString[0];
  uint8_t* finale = &finalString[0];
  
  obj.push(my,&label1[0],1);
  obj.push(other,&label2[0],2);
  obj.push(another,&label3[0],3);
  obj.push(finale,&label4[0],4);
  
  printf("total nodes in obj is:%i\n",obj.nodeCount());
  
  uint8_t* serialised_data = 0;
  uint8_t* transfered_data = 0;
  uint8_t* entropytestdata = 0;

  serialised_data = obj.getSerial();

  obj2 = obj2.buildDataObject(serialised_data);
  printf("total nodes created in obj2 is:%i\n",obj2.nodeCount());

  transfered_data = obj2.getSerial();

  
  obj3 = obj3.buildDataObject(transfered_data);
  printf("total nodes created in obj3 is:%i\n",obj3.nodeCount());

  entropytestdata = obj3.getSerial();
  obj4 = obj4.buildDataObject(entropytestdata);
  printf("total nodes created in obj4 is:%i\n",obj4.nodeCount());

  printf("--------------- obj 1 ----------\n");
  obj.readAll();
  printf("--------------- obj 2 ----------\n");
  obj2.readAll();
  printf("--------------- obj 3 ----------\n");
  obj3.readAll();
  printf("--------------- obj 4 ----------\n");
  obj4.readAll();
  //obj5.readAll();
}
		  
