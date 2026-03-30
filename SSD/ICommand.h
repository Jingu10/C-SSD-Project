#pragma once
#include <string>

class CommandHandler;

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual std::string execute(CommandHandler& handler) = 0;
};