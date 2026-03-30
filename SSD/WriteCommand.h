#pragma once
#include <string>
#include <cstdint>
#include "ICommand.h"

class WriteCommand : public ICommand {
    int _addr;
    uint32_t _value;
public:
    WriteCommand(int addr, uint32_t value) : _addr(addr), _value(value) {}

    std::string execute(CommandHandler& handler) override;
};