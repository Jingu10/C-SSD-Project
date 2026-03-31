#include <string>
#include "WriteCommand.h"
#include "CommandHandler.h"

std::string WriteCommand::execute(CommandHandler& handler) {
    handler.write(_addr, _value);

    return "SUCCESS\n";
}