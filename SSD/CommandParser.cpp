#include <memory>
#include <string>
#include <cstdint>
#include <sstream>
#include <exception>
#include "CommandParser.h"
#include "ICommand.h"
#include "ReadCommand.h"
#include "WriteCommand.h"

CommandParser::CommandParser() {}

std::unique_ptr<ICommand> CommandParser::parse(const std::string& request) const {
    if (request.empty()) {
        // 입력 없음
    }
    
    std::istringstream iss(request);
    std::string cmd;
    iss >> cmd;
    
    // 쓰기
    if (cmd == "W") {
        int addr;
        std::string valueStr;

        // 필수 토큰 검사
        if (!(iss >> addr >> valueStr))
            throw std::exception("Invalid format");

        // 여분 토큰 검사
        std::string extra;
        if (iss >> extra)
            throw std::exception("Invalid format");

        // 주소 범위 검사
        if (addr < 0 || addr > 99)
            throw std::exception("주소 범위 초과");

        // 16진수 문자열 -> uint32_t
        uint32_t value = 0;
        std::stringstream ss;
        ss << std::hex << valueStr;
        ss >> value;

        return std::make_unique<WriteCommand>(addr, value);
    }

    else if (cmd == "R") {
        int addr;
        // 필수 토큰 검사
        if (!(iss >> addr))
            throw std::exception("Invalid format");

        // 여분 토큰 검사
        std::string extra;
        if (iss >> extra)
            throw std::exception("Invalid format");

        // 주소 범위 검사
        if (addr < 0 || addr > 99)
            throw std::exception("주소 범위 초과");

        return std::make_unique<ReadCommand>(addr);
    }
    else {
        throw std::exception("Unknown command");
    }

}
