#include <iostream>

#include "../include/server/Server.h"

int main()
{   
    std::cout << "[INFO]: Server Created. Starting Execution..." << std::endl;

    Server::start(8080, 250);

    return 0;
}