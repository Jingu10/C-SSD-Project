#include <string>
#include <memory>
#include <utility>
#include <exception>
#include "CommandHandler.h"
#include "CommandParser.h"
#include "SSDMemory.h"

CommandHandler::CommandHandler(std::unique_ptr<CommandParser> parser, SSDMemory& memory)
	: _parser(std::move(parser)), _memory(memory) { }

std::string CommandHandler::handle(const std::string& request) {
	try {
		auto command = _parser->parse(request);
		return command->execute(*this);
	}
	catch (std::exception& e){
		return "ERROR\n";
	}
}

void CommandHandler::write(size_t addr, uint32_t value) { 
	_memory.write(addr, value); 
}

uint32_t CommandHandler::read(size_t addr) {
	return _memory.read(addr);
}
