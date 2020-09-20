#ifndef IDMAN_H
#define IDMAN_H
#define NULL = 0
#define BYTESIZE int(sizeof(unsigned char*))

#include <sodium.h>
#include <iostream>
#include <string>
#include <cstring>
#include "object.h"

//manages own identity as a network node, adds public key to a passing message, encrypts a message to be sent and decrypts a message
//intended for this node by wrapping or unwrapping messages approprietely
class IDMan{

  Object identity;
  unsigned char* publicKey = NULL, privateKey = NULL;
  std::string node_name;
  void createKeyPair();
  void createNodeName();
  
  public:

    IDMan();
    std::string getPublicKey();
    std::string getNodeName();
    unsigned char* getPublicKey();
    Object unwrapIdentity(Object wrapped_identity);
    Object wrapIdentity(Object unwrapped_identity);

};

#endif
