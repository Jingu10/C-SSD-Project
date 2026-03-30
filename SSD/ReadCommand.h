#pragma once
#include <string>
#include "ICommand.h"
#include "CommandHandler.h"

class ReadCommand : public ICommand {
private:
    int _addr;

public:
    ReadCommand(int addr);
    std::string execute(CommandHandler& handler) override;
};