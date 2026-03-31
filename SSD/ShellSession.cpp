#include <iostream>
#include <utility>
#include <exception>
#include "ShellSession.h"
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/buffer.hpp"
#include "boost/system/detail/error_code.hpp"
#include <boost/asio/streambuf.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include "boost/asio/impl/read_until.hpp"
#include "boost/system/system_error.hpp"
#include "boost/asio/error.hpp"
#include "boost/asio/impl/write.hpp"
#include "CommandHandler.h"

ShellSession::ShellSession(tcp::socket socket, std::unique_ptr<CommandHandler> handler)
    : _socket(std::move(socket)), _handler(std::move(handler)) {
}

void ShellSession::run() {
    try {
        boost::asio::streambuf buf;
        while (true) {
            // 줄 단위 입력
            boost::system::error_code ec;
            boost::asio::read_until(_socket, buf, '\n', ec);

            // 파일 끝에 도달하면 종료
            if (ec == boost::asio::error::eof) break;
            else if (ec) throw boost::system::system_error(ec);

            // 명령어 받기
            std::istream is(&buf);
            std::string request;
            std::getline(is, request);

            // 핸들러 호출
            std::string response = _handler->handle(request);
            
            // 응답
            boost::asio::write(_socket, boost::asio::buffer(response));
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}