#include "../header/receive.h"

Receive::Receive(std::string _IP, int _PORT):IP(_IP), PORT(_PORT){

  if(IP == "" || PORT == 0){

    printf("no address or port number");
  }
};

bool Receive::Connect(){

   
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
      
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 
    
    if(inet_pton(AF_INET, IP.data(), &serv_addr.sin_addr)<=0){
      
        printf("\n address not found");
        return false;
    }
      
    if( connect(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
      
       return false;
    }else{

      return true;
    }
}

bool Receive::Read(){

  message_pos = 0;
  message_pos = read(listenfd, rec_stack[selected_stack], buffer_size -1);
  if(message_pos < 0)
    return false;
  return true;
}

void Receive::selectBuffer(int  buffer_selection){

  selected_stack = buffer_selection;
}

std::string Receive::getAsString(){

  return std::string(reinterpret_cast<char*>(rec_stack[selected_stack]));
}

unsigned char* Receive::getAsBytes(){

  return reinterpret_cast<unsigned char*>(rec_stack[selected_stack]);
}

void Receive::Close(){

  close(listenfd);
}

//deep copy conscructor
Receive::Receive(const Receive &r){

  //for number of stacks copy over buffer size of data over
  for(int s = 0; s < (int) stack_num; s++)
    for(int b = 0; b < (int) buffer_size; b++)
      rec_stack[s][b] = r.rec_stack[s][b];
}

//gracefull deconstruction
Receive::~Receive(){

  Close();
}

