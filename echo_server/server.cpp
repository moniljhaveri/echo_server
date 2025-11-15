#include "server.h"
#include <arpa/inet.h> // For inet_ntoa


EchoSocket::EchoSocket(int ip_address, int type, int protocol)
{
    ip_address_ = ip_address; 
    type_ = type; 
    protocol_ = protocol;
    sockfd_ = socket(AF_INET, SOCK_STREAM, protocol_);
    socketAddress_.sin_family = AF_INET;
    socketAddress_.sin_port = htons(7);
    socketAddress_.sin_addr.s_addr = INADDR_ANY;
    


    if(sockfd_ == -1)
    {
        std::cout << "Failed to create socket" << std::endl;
        return;
    }
    std::cout << "Socket created successfully" << std::endl;
    bind(sockfd_, (struct sockaddr*)&socketAddress_, sizeof(socketAddress_));
    listen(sockfd_, 5);
    struct sockaddr_in clientAddress; 
    socklen_t clientAddrLen;
    int clientSocket = accept(sockfd_, (struct sockaddr*)&clientAddress, &clientAddrLen);
    auto pv4Addr = (struct sockaddr_in*)&clientAddress;
    auto ipAddr = pv4Addr->sin_addr;
    char clientIp[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ipAddr, clientIp, INET_ADDRSTRLEN);
    std::cout << "Client connected from IP: " << clientIp << ", Port: " << pv4Addr->sin_port << std::endl;
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "message from client " << buffer << std::endl;
}
EchoSocket::~EchoSocket()
{
    close(sockfd_);
    std::cout << "Client disconnected" << std::endl; 
}