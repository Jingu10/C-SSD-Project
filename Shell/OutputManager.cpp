#include "OutputManager.h"

OutputManager::OutputManager() {
    // 프로그램 시작 시 output.txt를 엽니다. (기존 내용 유지하려면 std::ios::app 추가)
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
    }
}

void OutputManager::printInput(const std::string& input) {
    if (outFile.is_open()) {
        outFile << "shell> " << input << "\n";
    }
}