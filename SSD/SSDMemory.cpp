#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include "SSDMemory.h"
#include <exception>

SSDMemory::SSDMemory() {
	loadFromFile("nand.txt");
}

void SSDMemory::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        // 파일 없으면 기본값 0
        _memory.fill(0);
        return;
    }

    std::string line;
    size_t i = 0;
    while (std::getline(ifs, line) && i < SIZE) {
        uint32_t value = 0;
        std::stringstream ss;
        ss << std::hex << line;
        ss >> value;
        _memory[i++] = value;
    }

    // 남는 주소는 0으로 초기화
    for (; i < SSDMemory::SIZE; ++i) _memory[i] = 0;
}

uint32_t SSDMemory::read(size_t addr) const {
    if (addr >= SIZE) throw std::exception("주소 범위 초과");
    return _memory[addr];
}

void SSDMemory::write(size_t addr, uint32_t value) {
    if (addr >= SIZE) throw std::exception("주소 범위 초과");
    _memory[addr] = value;
}