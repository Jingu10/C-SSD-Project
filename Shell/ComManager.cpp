#include "ComManager.h"
#include <iostream>

using boost::asio::ip::tcp;

ComManager::ComManager() : ssd_socket(io) {}

void ComManager::connectToSSD() {
    ssd_socket.connect(tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 12345));
}

std::string ComManager::sendCommandLineToSSD(const std::string& commandLine) {

	boost::asio::write(ssd_socket, boost::asio::buffer(commandLine + '\n'));

	boost::asio::streambuf buffer;;
	boost::asio::read_until(ssd_socket, buffer, '\n');

	std::string reply(
		boost::asio::buffers_begin(buffer.data()),
		boost::asio::buffers_end(buffer.data())
	);

	return reply;
}