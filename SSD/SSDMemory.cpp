#include <cstdint>
#include <fstream>
#include <string>
#include <exception>
#include <iomanip>
#include "SSDMemory.h"

SSDMemory::SSDMemory() {
	loadFromFile("nand.txt");
}

void SSDMemory::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);

    std::string line;
    size_t i = 0;

    if (ifs) {
        while (std::getline(ifs, line) && i < SIZE) {
            uint32_t value = 0;

            // 16진수 파싱
            try {
                value = std::stoul(line, nullptr, 16);
            }
            catch (...) {
                value = 0; // 잘못된 값은 0 처리
            }

            _memory[i++] = value;
        }
    }

    // 0으로 채우기
    for (; i < SIZE; ++i) {
        _memory[i] = 0;
    }

    // 파일 재생성
    saveToFile(filename);
}

void SSDMemory::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::trunc);

    if (!ofs) {
        throw std::exception("파일 쓰기 실패");
    }

    for (size_t i = 0; i < SIZE; ++i) {
        ofs << std::uppercase
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << _memory[i]
            << "\n";
    }
}

uint32_t SSDMemory::read(size_t addr) const {
    if (addr >= SIZE) throw std::exception("주소 범위 초과");
    return _memory[addr];
}

void SSDMemory::write(size_t addr, uint32_t value) {
    if (addr >= SIZE) throw std::exception("주소 범위 초과");
    _memory[addr] = value;

    saveToFile("nand.txt");
}