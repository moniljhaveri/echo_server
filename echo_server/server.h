#pragma once
#include <iostream>
#include <string> 
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>



class EchoSocket
{
    int sockfd_; 
    int ip_address_; 
    int type_; 
    int protocol_; 
    sockaddr_in socketAddress_; 
    public: 
        explicit EchoSocket(int ip_address, int type, int protocol);  
        ~EchoSocket();
};