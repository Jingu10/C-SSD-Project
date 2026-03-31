#include <sstream>
#include <iostream>
#include <stdexcept> // 없어도 작동하는데?
#include <filesystem>
#include <fstream>
#include <boost/asio.hpp> // tcp 용
#include "ComManager.h"
#include "Validator.h"

using namespace std;

int main() {
	
	ComManager cm;
	Validator v;
	cm.connectToSSD();

	while (true) {
		string commandLine;
		cout << "shell> ";
		getline(cin, commandLine);

		if (v.isValidFormattingCommandLine(commandLine)) {
			istringstream ss(commandLine);

			string command;
			getline(ss, command, ' ');

			if (command == "write") {
				string LBA;
				getline(ss, LBA, ' ');
				if (v.isValidLBA(LBA)) {
					string VALUE;
					getline(ss, VALUE, ' ');
					if (v.isValidVALUE(VALUE)) {
						commandLine.replace(commandLine.find("write"), 5, "W");
						std::cout << cm.sendCommandLineToSSD(commandLine);
					}
					else {
						std::cout << "ERROR\n";
					}
				}
				else {
					std::cout << "ERROR\n";
				}
			}
			else if (command == "read") {
				string LBA;
				getline(ss, LBA, ' ');
				if (v.isValidLBA(LBA)) {
					commandLine.replace(commandLine.find("read"), 4, "R");
					std::cout << cm.sendCommandLineToSSD(commandLine);
				} 
				else {
					std::cout << "ERROR\n";
				}
			}
			else if (command == "exit") {
				break;
			}
			else if (command == "help") {
				std::cout << "팀이름 : 나중에\n";
				std::cout << "팀 원 : 여진구, 허상운\n";
				std::cout << "각 명령어 사용 법\n";

				std::cout << "write <LBA> <VALUE> : Write Value on Logical Block Address with LBA number.\n";
				std::cout << "read <LBA> : Read Value from LBA with LBA number.\n";
				std::cout << "help : Show how to use each command.\n";
				std::cout << "fullwrite <VALUE> : Write Value on All LBA (0 ~ 99).\n";
				std::cout << "fullread <VALUE> : Read Value from all LBA.\n";
				std::cout << "test <No_TestName> : Test command lines on test script named No_TestName.\n";
				std::cout << "testall : Test All test scripts.\n";
			}
			else if (command == "fullwrite") {
				string VALUE;
				getline(ss, VALUE, ' ');
				if (v.isValidLBA(VALUE)) {
					// fullwrite 수행
				}
				else {
					std::cout << "ERROR\n";
				}
			}
			else if (command == "fullread") {

			}
			else if (command == "test") {
				string No_TestName;
				getline(ss, No_TestName, ' ');
				if (v.isValidTestFile(No_TestName)) {
					// 파일 열어서 하나씩 전송. 
				}
				else {
					std::cout << "ERROR\n";
				}
			}
			else if (command == "testall") {

			}
		}
		else {
			std::cout << "INVALID COMMAND\n";
			continue;
		}
	}
}