#include <sstream>
#include <iostream>
#include <stdexcept> // 이거 없어도 되긴 한데..

using namespace std;

// 잘못된 명령어 입력 및 인자 갯수 검증
// Fail 시 SSD에게 명령어 미전송 및 "INVALID COMMAND" 출력
// 값 범위 검증은, 이후의 커맨드 검증에서 수행 (커맨드에 따라 에러 출력이 다르기 때문)
bool isValidFormattingCommandLine(string& commandLine) {
	istringstream ss(commandLine);
	string stk;
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
	else if (stk == "read") {
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
	else if (stk == "exit" || stk == "help" || stk == "fullwrite" || stk == "fullread" || stk == "test" || stk == "testall") {
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

bool isValidLBA(string LBA) {
	try {
		int n = stoi(LBA);
		if (n >= 0 && n <= 99) return true;
		else return false;
	}
	catch (const invalid_argument& e) {
		return false;
	} catch(const out_of_range& e) {
		return false;
	}

	return true;
}

bool isValidVALUE(string& VALUE) {

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

bool sendCommandLineToSSD(string& commandLine) {

	std::cout << "send: " << commandLine << '\n';

	return true;
}

int main() {

	while (true) {
		string commandLine;
		cout << "shell> ";
		getline(cin, commandLine);

		if (isValidFormattingCommandLine(commandLine)) {
			istringstream ss(commandLine);

			string command;
			getline(ss, command, ' ');

			if (command == "write") {
				string LBA;
				getline(ss, LBA, ' ');
				if (isValidLBA(LBA)) {
					string VALUE;
					getline(ss, VALUE, ' ');
					if (isValidVALUE(VALUE)) {
						sendCommandLineToSSD(commandLine);
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
				if (isValidLBA(LBA)) {
					sendCommandLineToSSD(commandLine);
				} 
				else {
					std::cout << "ERROR\n";
				}
			}
			else if (command == "exit") {
				break;
			}
			else if (command == "help") {

			}
			else if (command == "fullwrite") {

			}
			else if (command == "fullread") {

			}
			else if (command == "test") {

			}
			else if (command == "testall") {

			}
		}
		else {
			std::cout << "INVALID COMMAND\n";
			continue;
		}


	}
#if 0 // test
	while (getline(ss, command, ' ')) {
		cout << command << '\n';
	}
#endif
	

}