#include <iostream>
#include <signal.h>
#include "server.h"

bool start = true;
void signalHandler(int sig)
{
    std::cout << "Shutting Down EchoServer" << std::endl; 
    start = false;
}

int main()
{
    auto echoServer = EchoSocket(120, 7, 0);
    signal(SIGINT, signalHandler);

    echoServer.run();
    while(start)
    {

    }
    echoServer.exit();
    return 0; 
}