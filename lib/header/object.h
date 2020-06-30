#ifndef OBJECT_H
#define OBJECT_H
#define NULL = 0
#define BYTESIZE int(sizeof(unsigned char*))

#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>

//This class will manage a data structure encoding data similar to ASN1s
//BER - functions contain operations for linked list type architecture
//and serialising/deserialising too and from bytes (unsigned char*)
//this is all an experiment this mustnt reflect on my knowledge
class Object{

  struct Node{

      struct Node *next = NULL;
      uint8_t* data = NULL;
      int8_t localsize = 0;
      int8_t metadata = 0;
      uint8_t* label = NULL;
  };

  struct Node head;

  int getType(struct Node*);
  int getLabelSize(struct Node*);
  uint8_t getLocalSize(struct Node*);
  
  public:

    Object();

    //push data then name data label and its type, for now the types are as follows:
    //'1' is "custom",'2' is "folder",'4' is "string",'8' is "uint8", reserves lots of possibilities
    ///TD:remember to zero memory before rolling out - omg dont forget garbage either
    bool push(uint8_t[], uint8_t[], int);
    
    //returns the node as bytes 
    void getSerialisedNode(struct Node*, uint8_t[]);

    //writes all data in node on left to array on right  
    void getSerialisedObject(struct Node*, uint8_t[]);

    //assigns node in left args with data in right, returns pos of next node
    int serial2Node(struct Node*, uint8_t*);
    int getTotalSize(struct Node*);
  
    void readAll();
    
};

#endif
