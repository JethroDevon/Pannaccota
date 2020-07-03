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

  lenode->localsize = (strlen((char*)lenode->data) + strlen((char*)datalabel) + 2); 
  
  //link node to head
  lenode->next = head.next;
  head.next = lenode;

  return true;
}

void Object::push(struct Node* node){

  struct Node* i_node = head.next;
  while(i_node != NULL){

    i_node = i_node->next;
  }
  
  i_node->next = node;
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

//returns serial data cointained in entire data structure
uint8_t* Object::getSerial(){

  uint8_t* data = 0;
  data = (uint8_t*) malloc(getTotalSize());
  getSerialisedObject(head.next,data);
  return data;
}

//returns the serialised data contained from that node onwards in the arguments on the right
void Object::getSerialisedObject(struct Node* node, uint8_t serialised_object[]){

  //create object to append data to
  uint8_t* accumulator = 0;
  unsigned int total_size = getTotalSize(node) + 4;
  int accumulated_size = 0;
  accumulator = (uint8_t*) malloc(total_size);
  
  //iterate through linked lists serialising the nodes data
  while (node != NULL){

    int d_sz = getLocalSize(node)+1;
    uint8_t node_data[d_sz];

    getSerialisedNode(node, node_data);

    for(int i = total_size - (accumulated_size + d_sz); (accumulated_size + i) != total_size -1; i++)
      accumulator[i] = node_data[((accumulated_size + d_sz) - total_size) + i];
    
    accumulated_size += d_sz;
    node = node->next;
  }

  //whack those four bytes of integer at the front of the entire data structure
  for(int i = 0; i < 4; i++){
    
    uint8_t byte = (total_size >> 8 * i) & 0xff;
    memcpy(serialised_object+i,&byte,sizeof(uint8_t*));
  }
  
  memcpy(serialised_object+4,accumulator,total_size);
}

//can pop them in backwards for nativeness but what could I call args?
unsigned int Object::buildInt(uint8_t onefour, uint8_t twofour, uint8_t threefour, uint8_t fourfour){

  return int(onefour << 24 | twofour << 16| threefour << 8 | fourfour);
}

Object Object::buildDataObject(uint8_t* serialdata){
  
  //create empty object
  Object obj;
 
  unsigned int totalsize = buildInt(serialdata[3], serialdata[2], serialdata[1],serialdata[0]);
  memcpy(serialdata,serialdata+4,totalsize); //shift serial data along by four
  
  //will find each position of a node and 
  int startpos = 0; // there are four bytes of integer at the very start of startpos
  int endpos = serialdata[0]; //this is the size of the node plus the startpos
  int detect_data_corruption = 0;
  
  while(startpos != totalsize){

    //getting location of where data on a node is stored to initialise variables in node with
    int size = serialdata[startpos];
    int type = serialdata[startpos+1] >> 4;
    int label_size = serialdata[startpos+1] & 15;
    int data_size = (size - (label_size + 2));
    uint8_t *data = 0;
    uint8_t *label = 0;   
    label = (uint8_t*)malloc(label_size);
    data = (uint8_t*)malloc(data_size);
    memcpy(label, serialdata + (startpos + 2), label_size);
    memcpy(data, serialdata + (startpos + label_size + 2), data_size );

    //data has been extracted from serial data and a node has been pushed onto a temporary object
    obj.push(data,label,type);
    
    //next positions of node are here
    startpos = (startpos + size) + 1;
    endpos = startpos + size;

    //its not unlikely the data structure is corrupted, the protocol isnt very robust, TD: maybe return an error object
    detect_data_corruption++;
    if(detect_data_corruption > 1024){

        break;
    }
  }

  return obj;
}

//*****************************************************************************************************************************

int Object::nodeCount(){

  struct Node* i_node = head.next;
  int count = 0;
  while(i_node != NULL){

    count++;
    i_node = i_node->next;
  }
  
  return count;
}

uint8_t Object::getLocalSize(struct Node* node){

  return node->localsize;
}

//returns the lower byte
int Object::getLabelSize(struct Node* node){

  return (node->metadata) & 15; //gets lower nibble
}

//returns the lower byte
const char* Object::getDataType(struct Node* node){

  int type = (node->metadata) >> 4; //gets lower nibble

  if(type == 1){

    return "custom";
  }else if(type == 2){

    return "folder";
  }else if(type == 4){

    return "string";
  }else{
    return "bytes";
  }
}

int Object::getTotalSize(struct Node* node){

  int total = 0;

  while (node != NULL){
    
     total += getLocalSize(node);
     node = node->next;
  }
     
  return total;
}

int Object::getTotalSize(){

  int total = 8;
  struct Node* node = head.next;
  while (node != NULL){
    
     total += getLocalSize(node);
     node = node->next;
  }
     
  return total;
}

int Object::getSerialSize(uint8_t* serialdata){

  return buildInt(serialdata[0],serialdata[1],serialdata[2],serialdata[3]);
}

void Object::readAll(){

  struct Node* node = head.next;
  while(node != NULL){

    printf("localsize: %i\n",(int)node->localsize);    
    printf("metadata: %i\n",(int)node->metadata);
    printf("datatype: %s\n", getDataType(node));
    printf("label: %s\n",node->label);
    printf("data:%s\n\n",node->data);
    node = node->next;
  }
}
