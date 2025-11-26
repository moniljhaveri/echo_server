#include "server.h"
#include <arpa/inet.h> // For inet_ntoa
#include <thread>


EchoSocket::EchoSocket(int ip_address, int type, int protocol)
{
    ip_address_ = ip_address; 
    type_ = type; 
    protocol_ = protocol;
    listenerSocket_ = socket(AF_INET, SOCK_STREAM, protocol_);
    socketAddress_.sin_family = AF_INET;
    socketAddress_.sin_port = htons(7);
    socketAddress_.sin_addr.s_addr = INADDR_ANY;

    if(listenerSocket_ == -1)
    {
        std::cout << "Failed to create socket" << std::endl;
        return;
    }
}
void EchoSocket::run() 
{

    bind(listenerSocket_, (struct sockaddr*)&socketAddress_, sizeof(socketAddress_));
    listen(listenerSocket_, 5);
    std::cout << "Listener Socket created successfully" << std::endl;

    while(true)
    {

        struct sockaddr_in clientAddress; 
        socklen_t clientAddrLen;
        int clientSocket = accept(listenerSocket_, (struct sockaddr*)&clientAddress, &clientAddrLen);
        auto pv4Addr = (struct sockaddr_in*)&clientAddress;
        auto ipAddr = pv4Addr->sin_addr;
        char clientIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &ipAddr, clientIp, INET_ADDRSTRLEN);
        if(clientSocket < 0) continue;
        std::cout << "Client connected from IP: " << clientIp << ", Port: " << pv4Addr->sin_port << std::endl;
        std::thread clientThread(&EchoSocket::handleClient, this, std::ref(clientSocket));
        clientThread.detach(); 
    }


}
void EchoSocket::handleClient(int clientSocket)
{

    while(true)
    {
        char buffer[1024] = {0};
        ssize_t bytes_read = read(clientSocket, buffer, sizeof(buffer));
        std::cout << buffer << std::endl;
        send(clientSocket, buffer, sizeof(buffer), 0);
    }


}
EchoSocket::~EchoSocket()
{
    close(listenerSocket_);

    std::cout << "Client disconnected" << std::endl; 
}