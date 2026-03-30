#pragma once
#include <string>
#include <memory>
#include "ICommand.h"

class CommandParser {
public:
    CommandParser();

    std::unique_ptr<ICommand> parse(const std::string& request) const;
};