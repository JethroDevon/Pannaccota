#ifndef OBJECT_H
#define OBJECT_H
#define NULL = 0

#include <iostream>
#include <string>
#include <cstring>

//dynamic linked list of unsigned chars this is a simple concept that is
//garuanteed to be problematic enough for person who is not warmed up
class Object{

  struct Node{

      struct Node *next = NULL;
      unsigned char* data;
      unsigned char localsize = 0;
      unsigned char metadata = 0;
      std::string label = "";
  };

  struct Node head;
  struct Node sub;  
  
  public:

    Object();

    ///linked list operations

    //push data then name data label and its type, for now the types are as follows:
    //'1' is "custom",'2' is "folder",'3' is "string",'4' is "uint8", reserves lots of possibilities
    ///remember to zero memory before rolling out - omg dont forget garbage either
    void push(unsigned char*, std::string, int);
    //void append(struct Node*, unsigned char*);
    //void pop();
    //void insert(struct Node*, unsigned char*);
  
    ///object operations
    unsigned char* get();
    void getAll();
};

#endif
