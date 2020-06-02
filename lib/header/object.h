#ifndef OBJECT_H
#define OBJECT_H
#define NULL = 0
#define BYTESIZE int(sizeof(unsigned char*))

#include <iostream>
#include <string>
#include <cstring>

//dynamic linked list of unsigned chars this is a simple concept that is
//garuanteed to be problematic enough for person who is not warmed up
class Object{

  struct Node{

      struct Node *next = NULL;
      unsigned char* data;
      int localsize = 0;
      unsigned char metadata = 0;
      std::string label = "";
  };

  struct Node head;
  struct Node sub;

  int getType(struct Node*);
  int getLocalSize(struct Node*);
  int getTitleSize(struct Node*);
  
  public:

    Object();

    //push data then name data label and its type, for now the types are as follows:
    //'1' is "custom",'2' is "folder",'3' is "string",'4' is "uint8", reserves lots of possibilities
    ///TD:remember to zero memory before rolling out - omg dont forget garbage either
    void push(unsigned char*, std::string, int);
    void addNestedData(struct Node*);///TD:am sure is a super elegant binary tree postifix style solution to do this but saving it for later
  
    ///object operations
    unsigned char* get();
    void readAll(struct Node*);
    
};

#endif
