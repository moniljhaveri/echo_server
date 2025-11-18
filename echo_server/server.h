#pragma once
#include <iostream>
#include <string> 
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>



class EchoSocket
{
    int listenerSocket_;
    int ip_address_; 
    int type_; 
    int protocol_; 
    sockaddr_in socketAddress_; 
    public: 
        explicit EchoSocket(int ip_address, int type, int protocol);  
        void handleClient(int clientSocket);
        void run(); 
        ~EchoSocket();
};