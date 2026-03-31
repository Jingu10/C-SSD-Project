#include <exception>
#include "SSDServer.h"
#include <iostream>

int main() {
    try {
        SSDServer server(12345);
        server.run();
    }
    catch (std::exception& e) {
        
    }
}