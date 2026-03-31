#pragma once
#include <boost/asio.hpp>

class ComManager {
    boost::asio::io_context io;
    boost::asio::ip::tcp::socket ssd_socket;
public:
    ComManager();
    void connectToSSD();
    std::string sendCommandLineToSSD(const std::string& commandLine);
};