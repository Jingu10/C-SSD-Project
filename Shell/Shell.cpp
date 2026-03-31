#include "Shell.h"
#include "Validator.h"
#include <sstream>
#include <vector>
#include <map>
#include <filesystem>

using namespace std;

Shell::Shell() {
    cm.connectToSSD();
}

void Shell::help() {
    om.print("Team Name : Super men");
    om.print("Team Member  : Jingu Yeo, Sangun Heo");
    om.print("How to use each command");

    om.print("write <LBA> <VALUE> : Write Value on Logical Block Address with LBA number.");
    om.print("read <LBA> : Read Value from LBA with LBA number.");
    om.print("help : Show how to use each command.");
    om.print("fullwrite <VALUE> : Write Value on All LBA (0 ~ 99).");
    om.print("fullread <VALUE> : Read Value from all LBA.");
    om.print("test <No_TestName> : Test command lines on test script named No_TestName.");
    om.print("testall : Test All test scripts.");
}

string Shell::write(const string& LBA, const string& VALUE) {
    return cm.sendCommandLineToSSD("W " + LBA + " " + VALUE);
}

string Shell::read(const string& lba) {
    return cm.sendCommandLineToSSD("R " + lba);
}

string Shell::fullWrite(const string& value) {
    vector<string> backup(100);
    for (int i = 0; i < 100; i++) backup[i] = read(to_string(i));

    bool success = true;
    int failIdx = -1;
    for (int i = 0; i < 100; i++) {
        if (write(to_string(i), value) != "SUCCESS") {
            success = false;
            failIdx = i;
            break;
        }
    }

    if (success) {
        return "SUCCESS"; 
    }
    else {
        for (int i = 0; i <= failIdx; i++) write(to_string(i), backup[i]); 
        return "ERROR";
    }
}

void Shell::fullRead() {
    for (int i = 0; i < 100; i++) {
        string res = read(to_string(i));
        if (res == "ERROR") {
            om.print("ERROR");
            break;
        }
        om.print("LBA " + to_string(i) + ": " + res);
    }
}

void Shell::test(const string& fileName) {
    string filePath = "./ssd_test_scripts/" + fileName + ".txt";

    ifstream file(filePath);
    string line;
    bool pass = true;

    while (getline(file, line)) {
        
        if (!v.isValidLineInTestFile(line))
        {
            pass = false;
            break;
        }

        istringstream ss(line);
        string command, LBA, VALUE, expected;
        ss >> command;

        if (command == "write") {
            ss >> LBA >> VALUE >> expected;
            if (write(LBA, VALUE) != expected) pass = false;
        }
        else if (command == "read") {
            ss >> LBA >> expected;
            if (read(LBA) != expected) pass = false;
        }
        else if (command == "fullwrite")
        {
            ss >> VALUE >> expected;
            if (fullWrite(VALUE) != expected) pass = false;
        }
        if (!pass) break;
    }

    if (pass) om.print("[PASS] " + fileName);
    else om.print("[FAIL] " + fileName);
}

void Shell::testAll() {

}

void Shell::run() {
    while (true) {
        string commandLine;
        cout << "shell> ";
        getline(cin, commandLine);
        om.printInput(commandLine);

        if (!v.isValidFormattingCommandLine(commandLine)) {
            om.print("INVALID COMMAND");
            continue;
        }

        istringstream ss(commandLine);
        string command, LBA, VALUE, fileName;
        ss >> command;

        if (command == "exit") {
            break;
        }
        else if (command == "help") {
            help();
        }
        else if (command == "write") {
            ss >> LBA >> VALUE; // 인자 갯수 안맞는 경우는 isValidFormat... 에서 검증하였으므로, 여기선 보장 돼 있음.
            if (!v.isValidLBA(LBA) || !v.isValidVALUE(VALUE)) om.print("ERROR");
            else om.print(write(LBA, VALUE));
        }
        else if (command == "read") {
            ss >> LBA;
            if (!v.isValidLBA(LBA)) om.print("ERROR");
            else om.print(read(LBA));
        }
        else if (command == "fullwrite") {
            ss >> LBA;
            if (!v.isValidVALUE(LBA)) om.print("ERROR");
            else om.print(fullWrite(LBA));
        }
        else if (command == "fullread") {
            fullRead();
        }
        else if (command == "test") {
            ss >> fileName;
            if(!v.isValidTestFile(fileName)) om.print("ERROR");
            else test(fileName);
        }
        else if (command == "testall") {
            testAll();
        }
    }
}