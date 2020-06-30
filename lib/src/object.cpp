#include "../header/object.h"

Object::Object(){

  head.next = NULL;
}

///TD: char data can definately be too big due to not having a set size yet - can be used for overflow
bool Object::push(uint8_t chardata[], uint8_t datalabel[], int datatype){

  //create and init node
  struct Node* lenode = new Node;
  lenode->data =  chardata;
  lenode->label = datalabel;
  
  //adds length of label to first nibbleh of metadata byte
  lenode->metadata = strlen((char*)datalabel);
  
  //flips the appropriate bit for datatype in the second half of the metadata nibbleh
  if(datatype <= 4 && datatype > 0){

      lenode->metadata |= 1UL << ((4 + datatype) -1);  
  }

  lenode->localsize = (strlen((char*)lenode->data) + strlen((char*)datalabel) +3); 
 
  //link node to head
  lenode->next = head.next;
  head.next = lenode;

  return true;
}

uint8_t Object::getLocalSize(struct Node* node){

  return node->localsize;
}

//returns the lower byte
int Object::getLabelSize(struct Node* node){

  return (node->metadata) & 15; //gets lower nibble
}

//returns the lower byte
int Object::getType(struct Node* node){

  return (node->metadata) >> 4; //gets lower nibble
}

int Object::getTotalSize(struct Node* node){

  int total = 0;

  while (node != NULL){
    
     total += getLocalSize(node);
     node = node->next;
  }
     
  return total;
}

//fugly function is fugly - play with unique pointers later
void Object::getSerialisedNode(struct Node* node, uint8_t serialised_node[]){

  int lcl_sz = getLocalSize(node);
  int lbl_sz = getLabelSize(node);
  int d_sz = strlen((char*)node->data);
  
  memcpy(serialised_node,&lcl_sz,1);
  memcpy(serialised_node+1,&node->metadata,1);
  memcpy(serialised_node+2,&node->label[0],lbl_sz);
  memcpy(serialised_node+(lbl_sz+2),&node->data[0],d_sz);
}

//returns the entire diserialised object as a stream of binary
void Object::getSerialisedObject(struct Node* node, uint8_t serialised_object[]){

  //create object to append data to
  uint8_t* accumulator = 0;
  int total_size = 0;
 
  accumulator = (uint8_t*) malloc(getTotalSize(node));
  
  //iterate through lists serialising nodes
  while (node != NULL){

    int d_sz = getLocalSize(node);
    uint8_t node_data[d_sz];

    getSerialisedNode(node, node_data);

    for(int i = 0; i < d_sz-1; i++)
      accumulator[total_size + i] = node_data[i];

    total_size += d_sz;
    node = node->next;
  }

  memcpy(serialised_object,accumulator,total_size);
}


//returning size should mark where to extract the next node
int Object::serial2Node(struct Node* node, uint8_t* node_data){

  uint8_t out = node_data[200];
  printf("a char is:%c",out);
 
  return (int) 0;
} 

//to be in a debug version, its not pretty
void Object::readAll(){

  struct Node* temp = head.next;
  int t_size = getTotalSize(temp);
  uint8_t* to = 0;
  to = (uint8_t*) malloc(t_size);
  getSerialisedObject(temp,to);

  for(int i = 0; i < t_size;i++)
    printf("%c",(char)to[i]);

}
