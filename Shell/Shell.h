#pragma once
#include "ComManager.h"
#include "OutputManager.h"
#include "Validator.h"

class Shell {
    ComManager cm;
    OutputManager om;
    Validator v;
public:
    Shell();
    void run();
private:
    std::string write(const std::string& LBA, const std::string& VALUE);
    std::string read(const std::string& LBA);
    std::string fullWrite(const std::string& VALUE);
    void fullRead();
    void test(const std::string& fileName);
    int extract_number(const std::string& filename);
    void testAll();
    void help();
};