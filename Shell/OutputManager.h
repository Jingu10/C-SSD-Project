#pragma once
#include <fstream>
#include <iostream> // for std::cout

class OutputManager {
private:
    std::ofstream outFile;

public:
    OutputManager();
    ~OutputManager();
    void print(const std::string& message);
    void printInput(const std::string& input);
};