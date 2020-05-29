#include "../header/object.h"

Object::Object(){

  head.next = NULL;
}

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
  
  //converts type into flipping the appropriate bit in the second half of the metadata nibbleh
  if(datatype <= 4 && datatype > 0){

      lenode->metadata |= 1UL << ((4 + datatype) -1);  
  }

  lenode->localsize = strlen(chardata);

  //link node to head
  lenode->next = head.next;
  head.next = lenode;
}

unsigned char* Object::get(){

  return head.next->data;
}

void Object::getAll(){

  struct Node* temp = new Node;
  temp = head.next;
  ///keep all this in here like this until is finished  
  while (temp != NULL){

    std::cout << temp->data << " " << strlen((char*)temp->data)<< " " << temp->label << " ";

    for(int x = 0; x < 8; x++){

      int y = ((byte >> x) & 1);
      std::cout << y;
    }
  
    std::cout << std::endl;
    temp = temp->next;
  }
}
