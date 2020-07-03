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

//file type is '1' is "custom",'2' is "folder",'4' is "string",'8' is "bytes",
//however the protocol I will use can wait for now


class Object{

  struct Node{

      struct Node *next = NULL;
      uint8_t* data = NULL;
      int8_t localsize = 0;
      int8_t metadata = 0;
      uint8_t* label = NULL;
  };

  struct Node head;

  int getLabelSize(struct Node*);
  uint8_t getLocalSize(struct Node*);
  
  public:

    Object();

    bool push(uint8_t[], uint8_t[], int);
    void push(struct Node*);
    
    //returns the node as bytes 
    void getSerialisedNode(struct Node*, uint8_t[]);

    //writes all data in node on left to array on right  
    void getSerialisedObject(struct Node*, uint8_t[]);
    uint8_t* getSerial();
    Object buildDataObject(uint8_t*);

    //reads all the data on the nodes on the object
    void readAll();
  
    //builds an unsigned integer with four bytes - might build helper class which is aware of what processor is working on
    unsigned int buildInt(uint8_t, uint8_t, uint8_t, uint8_t);    
    int getTotalSize(struct Node*);
    int getTotalSize();
    int getSerialSize(uint8_t*);
    int nodeCount();
    const char* getDataType(struct Node*);

};

#endif
