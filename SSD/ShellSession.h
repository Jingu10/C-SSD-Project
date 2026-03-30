#pragma once
#include "CommandHandler.h"
#include "boost/asio/ip/tcp.hpp"
#include <memory>

using boost::asio::ip::tcp;

class ShellSession {
private:
    tcp::socket _socket;
    std::unique_ptr<CommandHandler> _handler;

public:
    ShellSession(tcp::socket socket, std::unique_ptr<CommandHandler> handler);
    void run();

};