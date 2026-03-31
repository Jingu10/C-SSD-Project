#include <iostream>
#include <utility>
#include <memory>
#include "SSDServer.h"
#include "ShellSession.h"
#include "CommandHandler.h"
#include "CommandParser.h"
#include "boost/asio/ip/tcp.hpp"

SSDServer::SSDServer(short port)
    : _acceptor(_io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

void SSDServer::run() {
    tcp::socket socket(_io);
    _acceptor.accept(socket);

    auto parser = std::make_unique<CommandParser>();
    auto handlerPtr = std::make_unique<CommandHandler>(std::move(parser), _memory);
    ShellSession session(std::move(socket), std::move(handlerPtr));
    session.run();
}