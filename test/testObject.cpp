#include "../lib/src/object.cpp"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


Object obj, obj2, obj3, obj4, obj5, obj6, obj7, obj8;
uint8_t* data = 0;

int main( int argc, const char* argv[] ){

  unsigned char myString [] = "This is my string";
  unsigned char otherString [] = "This also is my string";
  unsigned char anotherString [] = "This is yet another string";
  unsigned char finalString [] = "This is my final string";

  unsigned char label1 [] = "keys";
  unsigned char label2 [] = "cmd or msg";
  unsigned char label3 [] = "start of file";
  unsigned char label4 [] = "one of six 1/6";
  
  uint8_t* my = &myString[0];
  uint8_t* other = &otherString[0];
  uint8_t* another = &anotherString[0];
  uint8_t* finale = &finalString[0];
  
  obj.push(my,&label1[0],8);
  obj.push(other,&label2[0],4);
  obj.push(another,&label3[0],2);
  obj.push(finale,&label4[0],1);
  
  uint8_t* serialised_data = 0;
  uint8_t* transfered_data = 0;
  uint8_t* entropytestdata = 0;
  uint8_t* data4 = 0;
  uint8_t* data5 = 0;
  uint8_t* data6 = 0;
  uint8_t* data7 = 0;
  
  serialised_data = obj.getSerial();


  
  printf("round1 data: b1 %i, b2 %i, b3 %i, b4 %i, localsize %i, meta %i\n", serialised_data[0],serialised_data[1],serialised_data[2],serialised_data[3],serialised_data[4],serialised_data[5]);
  obj2 = obj3.buildDataObject(serialised_data);
  transfered_data = obj2.getSerial();
  
  printf("round2 data: b1 %i, b2 %i, b3 %i, b4 %i, localsize %i, meta %i\n", transfered_data[0],transfered_data[1],transfered_data[2],transfered_data[3],transfered_data[4],transfered_data[5]);
  obj3 = obj3.buildDataObject(transfered_data);
  entropytestdata = obj3.getSerial();
  
  printf("round3 data: b1 %i, b2 %i, b3 %i, b4 %i, localsize %i, meta %i\n", entropytestdata[0],entropytestdata[1],entropytestdata[2],entropytestdata[3],entropytestdata[4],entropytestdata[5]);  
  obj4 = obj4.buildDataObject(entropytestdata);
  data4 = obj4.getSerial();
  
  printf("round4 data: b1 %i, b2 %i, b3 %i, b4 %i, localsize %i, meta %i\n", data4[0],data4[1],data4[2],data4[3],data4[4],data4[5]);
  obj5 = obj5.buildDataObject(data4);
  data5 = obj5.getSerial();
  
  printf("round5 data: b1 %i, b2 %i, b3 %i, b4 %i, localsize %i, meta %i\n", data5[0],data5[1],data5[2],data5[3],data5[4],data5[5]);
  obj6 = obj6.buildDataObject(data5);
  data6 = obj6.getSerial();

  printf("round6 data: b1 %i, b2 %i, b3 %i, b4 %i, localsize %i, meta %i\n", data6[0],data6[1],data6[2],data6[3],data6[4],data6[5]);
  obj7 = obj7.buildDataObject(data6);
  data7 = obj7.getSerial();
  
  printf("----------original obj 1 ----------\n");
  obj.readAll();
  printf("--------------- obj 2 ----------\n");
  obj2.readAll();
  printf("--------------- obj 3 ----------\n");
  obj3.readAll();
  printf("--------------- obj 4 ----------\n");
  obj4.readAll();
  printf("--------------- obj 5 ----------\n");
  obj5.readAll();
    printf("--------------- obj 6 ----------\n");
  obj6.readAll();
  
  for(int x = 0;x < 146; x++)
    printf(" %i",serialised_data[x]);

  printf("\n\n\n");

  for(int x = 0;x < 141; x++)
    printf(" %i",transfered_data[x]);

  printf("\n\n\n");

  for(int x = 0;x < 141; x++)
    printf(" %i",data6[x]);


}
		  
