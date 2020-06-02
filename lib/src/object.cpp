#include "../header/object.h"

Object::Object(){

  head.next = NULL;
}
///TD: char data can definately be too big due to not having a set size yet - can be used for overflow
void Object::push(unsigned char *chardata, std::string datalabel, int datatype){

  //create and init node
  struct Node* lenode = new Node;
  lenode->data = chardata;
  lenode->label = datalabel;
  
  //adds length of label to first nibbleh of metadata byte 
  int length = lenode->label.length();
  
  if(length > 15){
    lenode->label = lenode->label.substr(15);
  }
  
  lenode->metadata = (char)length;
  
  //flips the appropriate bit for datatype in the second half of the metadata nibbleh
  if(datatype <= 4 && datatype > 0){

      lenode->metadata |= 1UL << ((4 + datatype) -1);  
  }

  lenode->localsize = BYTESIZE + (BYTESIZE * strlen((const char*)chardata); //get exact size of all data pushed onto object
  
  //link node to head
  lenode->next = head.next;
  head.next = lenode;
}

int Object::getLocalSize(struct Node* node){

  return node->localsize;
}

//returns the lower byte
int Object::getTitleSize(struct Node* node){

  return (node->metadata) & 15; //gets lower nibble
}

//returns the lower byte
int Object::getType(struct Node* node){

  return (node->metadata) >> 4; //gets lower nibble
}

//pushes linked list onto sub node
void Object::addNestedData(struct Node* subnode){

  sub.next = subnode;
}

unsigned char* Object::get(){

  return head.next->data;
}

void Object::readAll(struct Node* node){

  temp = node.next;
  
  ///keep all this in here like this until is finished  
  while (temp != NULL){

    std::cout<< temp->data<<" "<<getLocalSize(temp)<<" "<<temp->label<<" "<<getTitleSize(temp)<<" "<<getType(temp)<<std::endl;
    temp = temp->next;
  }
}
