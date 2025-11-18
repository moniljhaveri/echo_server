#include <iostream>
#include "server.h"
int main()
{
    auto echoServer = EchoSocket(120, 7, 0);
    echoServer.run();
    return 0; 
}