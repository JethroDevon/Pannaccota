#include "../header/server.h"

Server::Server(int _PORT):PORT(_PORT){

    addr_len = sizeof(serv_addr);
    opt = 1;
    
    if ((servfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 

      failed = true;
      printf("could not create file descriptor, check permissions\n");
    } 

    if (setsockopt(servfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){ 

      failed = true;
      printf("port not available\n");
    }
    
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(PORT); 

    if (bind(servfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){

      failed = true;
      printf("could not bind \n");
    }  
  }


int Server::passConnection()
    //will hang here until connection is made
    if(listen(servfd, 3) < 0){

      failed = true;
      printf("error receiving connection");
    }
    
    return accept(servfd, (struct sockaddr *)&serv_addr,(socklen_t*)&addr_len);
}
