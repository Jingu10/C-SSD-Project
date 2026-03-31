#include <memory>
#include <string>
#include <cstdint>
#include <sstream>
#include <exception>
#include <regex>
#include "CommandParser.h"
#include "ICommand.h"
#include "ReadCommand.h"
#include "WriteCommand.h"
#include "SSDMemory.h"
#include <stdexcept>

CommandParser::CommandParser() {}

std::unique_ptr<ICommand> CommandParser::parse(const std::string& request) const {
    // 입력 없음
    if (request.empty()) {
        throw std::exception("Empty Request");
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
        if (addr < 0 || addr >= SSDMemory::SIZE)
            throw std::exception("주소 범위 초과");

        // value 정규식 검사
        static const std::regex pattern("^0x[0-9A-F]{8}$");
        if (!std::regex_match(valueStr, pattern)) {
            throw std::exception("Invalid VALUE format");
        }

        // 16진수 문자열 -> uint32_t
        uint32_t value = 0;
        try {
            value = std::stoul(valueStr, nullptr, 16);
        }
        catch (const std::invalid_argument&) {
            throw std::exception("Invalid VALUE format");
        }
        catch (const std::out_of_range&) {
            throw std::exception("VALUE out of range");
        }

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
        if (addr < 0 || addr >= SSDMemory::SIZE)
            throw std::exception("주소 범위 초과");

        return std::make_unique<ReadCommand>(addr);
    }
    else {
        throw std::exception("Unknown command");
    }

}
