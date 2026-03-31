#include "OutputManager.h"

OutputManager::OutputManager() {
    outFile.open("output.txt", std::ios::app);
}

OutputManager::~OutputManager() {
    if (outFile.is_open()) {
        outFile.close();
    }
}

void OutputManager::print(const std::string& message) {
    std::cout << message;

    if (outFile.is_open()) {
        outFile << message;
        outFile.flush();
    }
}

void OutputManager::printInput(const std::string& input) {
    if (outFile.is_open()) {
        outFile << "shell> " << input << "\n";
        outFile.flush();
    }
}