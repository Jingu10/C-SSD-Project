#include "Validator.h"
#include <sstream>
#include <filesystem>

bool Validator::isValidFormattingCommandLine(std::string commandLine) {
    std::istringstream ss(commandLine);
    std::string stk;
    getline(ss, stk, ' ');

    if (stk == "write") {
        if (getline(ss, stk, ' ')) {
            if (getline(ss, stk, ' ')) {
                if (!getline(ss, stk, ' ')) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else if (stk == "read" || stk == "fullwrite" || stk == "test") {
        if (getline(ss, stk, ' ')) {
            if (!getline(ss, stk, ' ')) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else if (stk == "exit" || stk == "help" || stk == "fullread" || stk == "testall") {
        if (!getline(ss, stk, ' ')) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Validator::isValidLBA(const std::string& LBA) {
    try {
        int n = stoi(LBA);
        if (n >= 0 && n <= 99) return true;
        else return false;
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
    catch (const std::out_of_range& e) {
        return false;
    }

    return true;
}

bool Validator::isValidVALUE(const std::string& VALUE) {

    if (VALUE.size() != 10) {
        return false;
    }
    if (VALUE[0] != '0') {
        return false;
    }
    if (VALUE[1] != 'x') {
        return false;
    }
    for (int i = 2; i < 10; i++) {
        if ((VALUE[i] >= '0' && VALUE[i] <= '9') || (VALUE[i] >= 'A' && VALUE[i] <= 'F')) {
            continue;
        }
        else {
            return false;
        }
    }

    return true;
}

bool Validator::isValidTestFile(const std::string& fileName) {

    if (fileName.find("_") == std::string::npos) {
        return false;
    }

    int idx = fileName.find("_");
    if (idx == 0) return false;

    std::string num = fileName.substr(0, idx);

    try {
        int n = stoi(num);

        std::string path = "./ssd_test_scripts/" + fileName + ".txt"; // 파일 존재 여부 확인
        if (!std::filesystem::exists(path)) return false;

        return true;
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
    catch (const std::out_of_range& e) {
        return false;
    }
    return true;
}

bool Validator::isValidLineInTestFile(const std::string& line) {
    std::istringstream ss(line);
    std::string command, LBA, VALUE, expected;

    ss >> command;

    if (command == "write") {
        if (!(ss >> LBA)) return false;
        if (!(ss >> VALUE)) return false;
        if (!(ss >> expected)) return false;
        if (!isValidLBA(LBA)) return false;
        if (!isValidVALUE(VALUE)) return false;
        return true;
    }
    else if (command == "read") {
        if (!(ss >> LBA)) return false;
        if (!(ss >> expected)) return false;
        if (!isValidLBA(LBA)) return false;
        return true;
    }
    else if (command == "fullwrite") {
        if (!(ss >> VALUE)) return false;
        if (!(ss >> expected)) return false;
        if (!isValidVALUE(VALUE)) return false;
        return true;
    }
}
