#include <sstream>
#include <iostream>
#include <stdexcept> // 없어도 작동하는데?
#include <filesystem>
#include <fstream>
#include <boost/asio.hpp> // tcp 용

using namespace std;
using boost::asio::ip::tcp;

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

bool isValidNo_TestName(string& No_TestName) {

	if (No_TestName.find("_") == string::npos) {
		return false;
	}
	
	int idx = No_TestName.find("_");
	if (idx == 0) return false;

	string num = No_TestName.substr(0, idx);

	try {
		int n = stoi(num);

		string path = "./ssd_test_scripts/" + No_TestName + ".txt"; // 파일 존재 여부 확인
		if (!filesystem::exists(path)) return false;

		return true;
	}
	catch (const invalid_argument& e) {
		return false;
	}
	catch (const out_of_range& e) {
		return false;
	}
	return true; 
}

string sendCommandLineToSSD(string& commandLine) {

	boost::asio::write(socket, boost::asio::buffer(commandLine + '\n'));

	boost::asio::streambuf buffer;;
	boost::asio::read_until(socket, buffer, '\n');

	std::string reply(
		boost::asio::buffers_begin(buffer.data()),
		boost::asio::buffers_end(buffer.data())
	);

	return reply;
}

void connectToSSD()
{
	boost::asio::io_context io;

	tcp::socket socket(io);
	socket.connect(tcp::endpoint(
		boost::asio::ip::make_address("127.0.0.1"), 12345));

}

int main() {
	connectToSSD();

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
						std::cout << sendCommandLineToSSD(commandLine);
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
					std::cout << sendCommandLineToSSD(commandLine);
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
				if (isValidLBA(VALUE)) {
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
				if (isValidNo_TestName(No_TestName)) {
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