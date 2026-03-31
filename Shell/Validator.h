#pragma once
#include <string>

class Validator {
public:
	bool isValidFormattingCommandLine(std::string commandLine);
	bool isValidLBA(const std::string& LBA);
	bool isValidVALUE(const std::string& VALUE);
	bool isValidTestFile(const std::string& fileName);
};