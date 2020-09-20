#include "../header/idman.h"

IDMan::IDMan(){

  createKeyPair();
}

void IDMan::createKeyPair(){

  //init pub and private keys and store in locally in file $nodename
  unsigned char publicKey[crypto_kx_PUBLICKEYBYTES];
  unsigned char privateKey[crypto_kx_SECRETKEYBYTES];
  crypto_kx_keypair(publicKey, privateKey);
}

void IDMan::createNodeName(){
  
  node_name = "empty";//TO-DO: change this to at least random numbers
  
  //get host name else use random num
  #ifdef __linux__ 

    char hostname[HOST_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    node_name(hostname);
  #elif _WIN_
    
    GetComputerName(infoBuf, &bufCharCount);
    node_name(infoBuf);
  #endif

    std::cout << "did i get the hostname? :" << node_name << std::endl;
}

unsigned char* IDMan::getPublicKey(){

  return publicKey;
}

std::string IDMan::getNodeName(){

  return node_name;
}

void IDMan::addChildIdentity(std::string hostname, std::string ip, unsigned char* publicKey){

  child.push(hostname, "hostname", 4);
  child.push(ip, "ip", 4);
  child.push(publicKey, "pkey", 8);
}
