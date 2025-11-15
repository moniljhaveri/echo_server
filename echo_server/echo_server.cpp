#include <iostream>
#include "server.h"
int main()
{
    auto echoServer = EchoSocket(120, 7, 0);
    return 0; 
}