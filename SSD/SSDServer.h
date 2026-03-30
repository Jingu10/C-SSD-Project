#pragma once
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/io_context.hpp"
#include "SSDMemory.h"

using boost::asio::ip::tcp;

class SSDServer {
private:
    boost::asio::io_context _io;
    tcp::acceptor _acceptor;
    SSDMemory _memory;

public:
    SSDServer(short port);
    void run();

};