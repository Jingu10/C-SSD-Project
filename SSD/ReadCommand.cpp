#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <ios>
#include "CommandHandler.h"
#include "ReadCommand.h"

ReadCommand::ReadCommand(int addr) : _addr(addr) {}

std::string ReadCommand::execute(CommandHandler& handler) {
    uint32_t value = handler.read(_addr);
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << value;
    return ss.str() + "\n";
}


