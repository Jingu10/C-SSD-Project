#pragma once
#include <string>
#include "CommandParser.h"
#include <memory>
#include "SSDMemory.h"
#include <cstdint>

class CommandHandler {
private:
    std::unique_ptr<CommandParser> _parser;
    SSDMemory& _memory;

public:
    CommandHandler(std::unique_ptr<CommandParser> parser, SSDMemory& memory);

    std::string handle(const std::string& request);
    void write(size_t addr, uint32_t value);
    uint32_t read(size_t addr);
};