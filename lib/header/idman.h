#ifndef IDMAN_H
#define IDMAN_H
#define NULL = 0
#define BYTESIZE int(sizeof(unsigned char*))

#include <sodium.h>
#include <iostream>
#include <string>
#include <cstring>
#include "object.h"

#ifdev __linux__

  #include <unistd.h>
  #include <limits.h>
#elif _WIN_

  #include <windows.h>
  #define INFO_BUFFER_SIZE 32767
  TCHAR  infoBuf[INFO_BUFFER_SIZE];
  DWORD  bufCharCount = INFO_BUFFER_SIZE;
#endif

//manages own identity as a network node, adds public key to a passing message, encrypts a message to be sent and decrypts a message
//intended for this node by wrapping or unwrapping messages approprietely
class IDMan{

  std::string node_name;
  IDMan();
  
  private:

    Object identity, parent, children;
    unsigned char publicKey = NULL, privateKey = NULL;
  
    std::string getPublicKey();
    std::string getNodeName();
    unsigned char* getPublicKey();

    //hostname, ip address, public key
    void addChildIdentity(std::string, std::string, unsigned char*);

    //true for encrypt false for decrypt \o/
    std::string symetricEncryption(std::string, bool);
    unsigned char* symetricEncryption(unsigned char*, bool);
    Object symetricEncryption(Object, bool);
    std::string asymetricEncryption(std::string, bool);
    unsigned char* asymetricEncryption(unsigned char*, bool);
    Object asymetricEncryption(Object, bool);
  
    void saveChildData();
    void loadChildData();
    void createKeyPair();
    void createNodeName();
  
  public:
  
    //Good 2 Go:Object returned contains all data for socket handler 
    Object requestNodeListG2G(std::string);
    Object returnNodeListG2G();
    Object sendCommandG2G(std::string, std::string);
    Object sendDataG2G(std::string, unsigned char*);

    //recieve data, decrypt into object containing instructions
    Object data2Object(unsigned char *);
};

#endif
